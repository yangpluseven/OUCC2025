#include "passes.h"
#include <algorithm>

namespace pass {

size_t LoopInvariantCodeMotion::_maxDistance = 10; // Default distance for LICM

bool isLoopInvariant(ir::Instruction *inst, ir::LoopInfo *loopInfo) {
  auto instKind = inst->getInstKind();

  switch (instKind) {
  case ir::InstKind::Branch:
  case ir::InstKind::Call:
  case ir::InstKind::Ret:
  case ir::InstKind::Store:
  case ir::InstKind::Load:
  case ir::InstKind::Alloca:
  case ir::InstKind::Phi:
  case ir::InstKind::Move:
    return false;
  }

  for (size_t i = 0; i < inst->getNumOperands(); i++) {
    auto operand = inst->getOperand(i);
    if (operand->getValueKind() == ir::ValueKind::Inst) {
      auto operandInst = static_cast<ir::Instruction *>(operand);
      if (loopInfo->inLoopBody(operandInst->getBlock())) {
        return false; // Operand is in the loop body, not invariant
      }
    }
  }
  return true; // All operands are invariant
}

bool LoopInvariantCodeMotion::onFunction(ir::Function *function) {
  if (function->loops.empty()) {
    return false; // No loops to optimize
  }
  function->calcIndexInFunc();
  for (auto loop : function->loops) {
    loop->calcLoopBody(function);
  }
  bool modified = false;
  for (int i = function->loops.size() - 1; i >= 0; i--) {
    auto loop = function->loops[i];
    auto beforeBlock = static_cast<ir::BasicBlock *>(
        function->getBlock(loop->getBeforeIndex()));
    for (int j = loop->getEnterIndex(); j < loop->getLeaveIndex(); j++) {
      auto block = static_cast<ir::BasicBlock *>(function->getBlock(j));
      if (block->loopInfo && block->loopInfo != loop) {
        j = block->loopInfo->getLeaveIndex() - 1; // Skip the inner loop body
        continue;
      }
      for (size_t k = 0;
           k < std::min(block->size(), LoopInvariantCodeMotion::_maxDistance);
           k++) {
        auto inst = static_cast<ir::Instruction *>(block->getInstruction(k));
        if (!isLoopInvariant(inst, loop)) {
          continue; // Not invariant, skip
        }
        auto instPtr = block->eraseInstruction(k);
        beforeBlock->insertInstruction(beforeBlock->size() - 1,
                                       std::move(instPtr));
        k--;
        modified = true; // Mark as modified
      }
    }
  }
  return modified;
}

} // namespace pass
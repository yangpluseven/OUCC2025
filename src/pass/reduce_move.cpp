#include "passes.h"

namespace pass {

bool ReduceMove::onFunction(riscv::MachineFunc *function) {
  bool modified = false;
  function->calcIndexInFunc();
  for (auto &block : *function) {
    block->calcIndexInBlock();
    auto mBlock = static_cast<riscv::MachineBlock *>(block.get());
    for (size_t i = 0; i < mBlock->size(); i++) {
      auto inst = mBlock->getMInst(i);
      if (inst->getMInstKind() == riscv::MInstKind::RR) {
        auto rrInst = static_cast<riscv::RR *>(inst);
        if (rrInst->getOp() != riscv::RROp::MV) {
          continue; // Only consider move operations
        }
        // Move a register to itself is redundant
        if (rrInst->getSrc(0) == rrInst->getDest()) {
          mBlock->eraseInstruction(i);
          modified = true;
          i--; // Adjust index after removal
          continue;
        }

        if (dynamic_cast<riscv::MReg *>(rrInst->getSrc(0))) {
          continue;
        }

        if (rrInst->getSrc(0)->getRegType()->getBasicKind() !=
            rrInst->getDest()->getRegType()->getBasicKind()) {
          continue; // Type mismatch, cannot optimize
        }

        // If the source instruction has only one use, we can replace it
        // directly with the destination register
        auto srcInst = static_cast<riscv::MachineInst *>(rrInst->getOperand(0));
        // Optimization between Blocks are too tricky, skip for now
        if (rrInst->getBlock() != srcInst->getBlock() ||
            srcInst->getMInstKind() == riscv::MInstKind::PhiNode) {
          continue; // Source and destination must be in the same block
        }

        if (rrInst->getIndexInBlock() != srcInst->getIndexInBlock() + 1) {
          continue; // The move must be immediately after the source
        }

        if (srcInst->getUses().size() == 1) {
          srcInst->setDest(rrInst->getDest());
          if (dynamic_cast<ir::VReg *>(rrInst->getDest())) {
            rrInst->replaceAllUsesWith(srcInst);
          }
          mBlock->eraseInstruction(i);
          modified = true;
          i--; // Adjust index after removal
          continue;
        }
      }
    }
  }
  return modified;
}

} // namespace pass
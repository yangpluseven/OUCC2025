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

        if (rrInst->isReturn) {
          continue; // Skip return instructions
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

        bool invalid = false;
        block->calcIndexInBlock();
        for (int j = srcInst->getIndexInBlock() + 1;
             j < rrInst->getIndexInBlock(); j++) {
          auto tmpInst = mBlock->getMInst(j);
          if (tmpInst->getMInstKind() == riscv::MInstKind::Call) {
            invalid = true; // Found a call instruction, cannot replace
            break;
          }
          if (tmpInst->getDest() == rrInst->getDest()) {
            invalid = true;
            break; // Found an instruction that uses the destination register
          }
          for (int k = 0; k < tmpInst->getNumOperands(); k++) {
            if (tmpInst->getSrc(k) == rrInst->getDest()) {
              invalid = true;
              break; // Found an instruction that uses the destination register
            }
          }
          if (invalid) {
            break; // No need to check further
          }
        }

        if (invalid) {
          continue; // Cannot replace if the destination is used in between
        }

        // if (rrInst->getIndexInBlock() != srcInst->getIndexInBlock() + 1) {
        //   continue; // The move must be immediately after the source
        // }

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
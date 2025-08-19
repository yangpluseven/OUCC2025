#include "passes.h"

namespace pass {

bool LowerBranchOpti::onFunction(riscv::MachineFunc *function) {
  bool modified = false;
  for (auto &blockPtr : *function) {
    auto block = static_cast<riscv::MachineBlock *>(blockPtr.get());
    for (size_t i = 1; i < block->size(); i++) {
      auto mInst = block->getMInst(i);
      if (mInst->getMInstKind() != riscv::MInstKind::Jump) {
        continue; // Only handle jump instructions
      }
      auto jumpInst = static_cast<riscv::Jump *>(mInst);
      if (!jumpInst->hasCond()) {
        continue; // Skip unconditional jumps
      }
      auto op = jumpInst->getOp();
      if (!(op == riscv::JumpOp::EQ || op == riscv::JumpOp::NE)) {
        continue; // Only handle EQ and NE conditions
      }
      auto cond = dynamic_cast<riscv::RRR *>(jumpInst->getOperand(0));
      if (!cond) {
        continue; // Skip if condition is not a RRR instruction
      }
      if (block->getMInst(i - 1) != cond) {
        continue; // Condition must be the previous instruction
      }
      if (cond->getUses().size() != 1) {
        continue; // Condition must be used only by this jump instruction
      }
      if (cond->getOp() == riscv::RRROp::SLT) {
        if (op == riscv::JumpOp::NE &&
            jumpInst->getSrc(1) == riscv::MReg::zero) {
          jumpInst->setOp(riscv::JumpOp::LT);
          jumpInst->setOperand(0, cond->getOperand(0));
          jumpInst->setOperand(1, cond->getOperand(1));
          block->eraseInstruction(i - 1);
          i--; // Adjust index after removal
        } else if (op == riscv::JumpOp::EQ &&
                   jumpInst->getSrc(1) == riscv::MReg::zero) {
          jumpInst->setOp(riscv::JumpOp::GE);
          jumpInst->setOperand(0, cond->getOperand(0));
          jumpInst->setOperand(1, cond->getOperand(1));
          block->eraseInstruction(i - 1);
          i--; // Adjust index after removal
        }
        modified = true;
      } else if (cond->getOp() == riscv::RRROp::SGT) {
        if (op == riscv::JumpOp::NE &&
            jumpInst->getSrc(1) == riscv::MReg::zero) {
          jumpInst->setOp(riscv::JumpOp::GT);
          jumpInst->setOperand(0, cond->getOperand(0));
          jumpInst->setOperand(1, cond->getOperand(1));
          block->eraseInstruction(i - 1);
          i--; // Adjust index after removal
        } else if (op == riscv::JumpOp::EQ &&
                   jumpInst->getSrc(1) == riscv::MReg::zero) {
          jumpInst->setOp(riscv::JumpOp::LE);
          jumpInst->setOperand(0, cond->getOperand(0));
          jumpInst->setOperand(1, cond->getOperand(1));
          block->eraseInstruction(i - 1);
          i--; // Adjust index after removal
        }
        modified = true;
      }
    }
  }
  return modified;
}

} // namespace pass
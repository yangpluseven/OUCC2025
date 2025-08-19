#include "passes.h"

namespace pass {

// Unfinished implementation (ATTENTION)
bool RemoveUnnecessaryInsts::onFunction(riscv::MachineFunc *function) {
  bool modified = false;
  for (auto &blockPtr : *function) {
    auto mBlock = static_cast<riscv::MachineBlock *>(blockPtr.get());
    for (size_t i = 0; i + 1 < mBlock->size(); i++) {
      auto mInst = mBlock->getMInst(i);
      auto mInstKind = mInst->getMInstKind();
      if (mInstKind == riscv::MInstKind::RRI) {
        auto rriInst = static_cast<riscv::RRI *>(mInst);
        auto op = rriInst->getOp();
        if (op == riscv::RRIOp::ADDI) {
          auto imm = rriInst->getImm();
          if (imm == 0) {
            // If the RRI instruction is an ADDI with immediate 0, it can be
            // removed
            mBlock->eraseInstruction(i);
            i--;
            modified = true;
          }
        }
      } else if (mInstKind == riscv::MInstKind::RRR) {
        auto rrrInst = static_cast<riscv::RRR *>(mInst);
        auto op = rrrInst->getOp();
        if (op == riscv::RRROp::ADD) {
          auto srcInst0 = rrrInst->getOperand(0);
          auto srcInst1 = rrrInst->getOperand(1);
        }
      }
    }
  }
  return modified;
}

} // namespace pass
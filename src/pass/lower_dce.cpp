#include "passes.h"

namespace pass {

bool LowerDCE::onFunction(riscv::MachineFunc *function) {
  bool modified = false;
  for (auto &blockPtr : *function) {
    auto mBlock = static_cast<riscv::MachineBlock *>(blockPtr.get());
    for (size_t i = 0; i + 1 < mBlock->size(); i++) {
      auto mInst = mBlock->getMInst(i);
      auto mInstKind = mInst->getMInstKind();
      switch (mInstKind) {
      case riscv::MInstKind::Fake:
      case riscv::MInstKind::Jump:
      case riscv::MInstKind::Call:
      case riscv::MInstKind::Load:
      case riscv::MInstKind::LoadFrom:
      case riscv::MInstKind::Store:
      case riscv::MInstKind::StoreTo:
      case riscv::MInstKind::PhiNode:
      case riscv::MInstKind::GetArg:
        // These instructions cannot be removed
        continue;
      }

      if (mInst->getUses().empty()) {
        mBlock->eraseInstruction(i);
        i--;
        modified = true;
      }
    }
  }
  return modified;
}

} // namespace pass
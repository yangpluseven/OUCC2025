#include "register.h"

namespace ir {
void VReg::addConflict(riscv::MReg *reg) { _conflictRegs.insert(reg); }

bool VReg::isConflictWith(riscv::MReg *reg) {
  return _conflictRegs.find(reg) != _conflictRegs.end();
}
} // namespace ir
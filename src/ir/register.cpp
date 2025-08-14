#include "register.h"

namespace ir {

std::unique_ptr<ir::BasicType> Reg::i32_t =
    std::make_unique<ir::BasicType>(ir::BasicKind::I32);
std::unique_ptr<ir::BasicType> Reg::f32_t =
    std::make_unique<ir::BasicType>(ir::BasicKind::F32);

void VReg::addConflict(riscv::MReg *reg) { _conflictRegs.insert(reg); }

bool VReg::isConflictWith(riscv::MReg *reg) {
  return _conflictRegs.find(reg) != _conflictRegs.end();
}
} // namespace ir
#include "riscv/machine_insts.h"
#include <stdexcept>
using namespace ir;

#define MAKE_VOID std::make_unique<BasicType>(BasicKind::VOID)

namespace riscv {
int MachineInst::_counter = 1;

MachineInst::MachineInst(std::unique_ptr<Type> type)
    : InstBase(std::move(type), _counter++) {
  assert(getType()->isBasic() && "MachineInst can only have a basic type.");
  switch (getBasicKind()) {
  case BasicKind::I32:
  case BasicKind::F32:
    _dest = new VReg(static_cast<BasicType *>(getType()), getID());
  default:
    return;
  }
}

MachineInst::MachineInst(std::unique_ptr<Type> type,
                         const std::vector<Value *> &useOperands)
    : InstBase(std::move(type), useOperands, _counter++) {
  assert(getType()->isBasic() && "MachineInst can only have a basic type.");
  switch (getBasicKind()) {
  case BasicKind::I32:
  case BasicKind::F32:
    _dest = new VReg(static_cast<BasicType *>(getType()), getID());
  default:
    return;
  }
}

std::string MachineInst::getName() const {
  if (_dest) {
    return _dest->str();
  }
  throw std::runtime_error("No available reg, getName should not be called");
}

std::vector<ir::Reg *> MachineInst::getRegs() const {
  std::vector<ir::Reg *> regs;
  auto readRegs = getRead();
  auto writeRegs = getWrite();

  regs.insert(regs.end(), readRegs.begin(), readRegs.end());
  regs.insert(regs.end(), writeRegs.begin(), writeRegs.end());
  return std::move(regs);
}
} // namespace riscv

#undef MAKE_VOID
#include "riscv/machine_func.h"

namespace riscv {

int MachineBlock::_counter = 0;

MachineBlock::MachineBlock() : BlockBase(_counter++) {}

MachineBlock::MachineBlock(int id) : BlockBase(id) { _counter = id + 1; }

// Currently the name must match the original LLVM IR basicblock (ATTENTION)
std::string MachineBlock::getLabel() const {
  return ".bb" + std::to_string(getID());
}
std::string MachineBlock::getName() const { return getLabel(); }

MachineFunc::MachineFunc(ir::Function *func, int localSize, int iCallerNum,
                         int fCallerNum)
    : FuncBase(std::make_unique<ir::BasicType>(ir::BasicKind::VOID),
               func->getRawName()),
      _origin(func), _localSize(localSize), _iCallerNum(iCallerNum),
      _fCallerNum(fCallerNum) {}

} // namespace riscv
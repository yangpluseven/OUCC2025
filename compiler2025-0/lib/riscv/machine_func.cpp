#include "riscv/machine_func.h"
#include "riscv/registers.h"

namespace riscv {

int MachineBlock::_counter = 0;

MachineBlock::MachineBlock() : BlockBase(_counter++) {}

MachineBlock::MachineBlock(int id) : BlockBase(id) { _counter = id + 1; }

// Currently the name must match the original LLVM IR basicblock (ATTENTION)
std::string MachineBlock::getLabel() const {
  return ".bb" + std::to_string(getID());
}
std::string MachineBlock::getName() const { return getLabel(); }

MachineFunc::MachineFunc(ir::Function *func)
    : FuncBase(std::make_unique<ir::BasicType>(ir::BasicKind::VOID),
               func->getRawName()),
      _origin(func) {
  initCallerNums();
}

void MachineFunc::initCallerNums() {
  size_t iSize = 0, fSize = 0;
  for (auto arg : _origin->getArgs()) {
    auto type = arg->getType();
    if (type->isBasic() && static_cast<ir::BasicType *>(type)->getBasicKind() ==
                               ir::BasicKind::F32) {
      fSize = std::min(fSize + 1, MReg::fCallerRegs.size());
    } else {
      iSize = std::min(iSize + 1, MReg::iCallerRegs.size());
    }
  }
  _iCallerNum = iSize;
  _fCallerNum = fSize;
  return;
}

void MachineFunc::initLocalOffsets() {
  int localSize = 0;
  auto block = _origin->getFirstBlock();
  for (auto &ptr : *block) {
    auto ir = static_cast<ir::Instruction *>(ptr.get());
    // Must place alloca at the front! (ATTENTION)
    if (!ir->isAlloca()) {
      break;
    }
    auto allocaInst = static_cast<ir::AllocaInst *>(ir);
    int size = allocaInst->getType()->getBaseType()->getSize() / 8;
    _localOffsets[allocaInst] = localSize;
    localSize += size;
  }
  _localSize = localSize;
  return;
}

void MachineFunc::initArgOffsets() {
  
}

} // namespace riscv
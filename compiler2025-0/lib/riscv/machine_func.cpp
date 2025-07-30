#include "riscv/machine_func.h"
#include "riscv/registers.h"

namespace riscv {

using ir::ValueKind;
using std::make_unique;
using std::unique_ptr;

int MachineBlock::_counter = 0;

MachineBlock::MachineBlock() : BlockBase(_counter++) {}

MachineBlock::MachineBlock(int id) : BlockBase(id) { _counter = id + 1; }

// Currently the name must match the original LLVM IR basicblock (ATTENTION)
std::string MachineBlock::getLabel() const {
  return ".bb" + std::to_string(getID());
}

std::string MachineBlock::getName() const { return getLabel(); }

MachineFunc::MachineFunc(ir::Function *func)
    : FuncBase(make_unique<ir::BasicType>(ir::BasicKind::VOID),
               func->getRawName()),
      _origin(func) {
  initCallerNums();
  initLocalOffsets();
  initArgOffsets();
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
  int iCallerNum = 0, fCallerNum = 0;
  auto args = _origin->getArgs();
  for (auto arg : args) {
    auto type = arg->getType();
    if (type->isBasic() && static_cast<ir::BasicType *>(type)->getBasicKind() ==
                               ir::BasicKind::F32) {
      fCallerNum++;
    } else {
      iCallerNum++;
    }
  }
  iCallerNum = std::min(iCallerNum, static_cast<int>(MReg::iCallerRegs.size()));
  fCallerNum = std::min(fCallerNum, static_cast<int>(MReg::fCallerRegs.size()));
  int iSize = 0, fSize = 0;
  for (auto arg : args) {
    auto type = arg->getType();
    if (type->isBasic() && static_cast<ir::BasicType *>(type)->getBasicKind() ==
                               ir::BasicKind::F32) {
      if (fSize < MReg::fCallerRegs.size()) {
        _argOffsets[arg] = {true, (fCallerNum - fSize - 1) * 8};
      } else {
        _argOffsets[arg] = {false, MReg::argsStackOffset(iSize, fSize)};
      }
      fSize++;
    } else {
      if (iSize < MReg::iCallerRegs.size()) {
        _argOffsets[arg] = {true, (iCallerNum - iSize - 1) * 8};
      } else {
        _argOffsets[arg] = {false, MReg::argsStackOffset(iSize, fSize)};
      }
      iSize++;
    }
  }
}

MachineInst *MachineFunc::handleArg(ir::Argument *arg, MachineBlock *block) {
  bool isInner = _argOffsets[arg].first;
  auto inst =
      make_unique<LoadFrom>(isInner ? LoadItem::INNER : LoadItem::OUTER,
                            arg->makeRegType(), _argOffsets[arg].second);
  auto machineInst = block->pushInstruction(std::move(inst));
  return static_cast<MachineInst *>(machineInst);
}

void MachineFunc::binary(ir::BinaryInst *inst, MachineBlock *block) {
  auto operand1 = inst->getOperand(0);
  auto operand2 = inst->getOperand(1);
  MachineInst *src1 = nullptr;
  if (operand1->isArg()) {
    src1 = handleArg(static_cast<ir::Argument *>(operand1), block);
  } else if (operand1->isInst()) {
    src1 = _instMap[static_cast<ir::Instruction *>(operand1)];
  }
  MachineInst *src2 = nullptr;
  if (operand2->isArg()) {
    src2 = handleArg(static_cast<ir::Argument *>(operand2), block);
  } else if (operand2->isInst()) {
    src2 = _instMap[static_cast<ir::Instruction *>(operand2)];
  }
  if (src1 && src2) {
    // TODO
    return;
  }
  if (src1 && operand2->isConstNum()) {
    // TODO
    return;
  }
  if (src2 && operand1->isConstNum()) {
    // TODO
    return;
  }
  if (operand1->isConstNum() && operand2->isConstNum()) {
    // TODO
    return;
  }
  // If we reach here, it means we have a problem with the operands
  throw std::runtime_error("Invalid operands for binary instruction");
}

void MachineFunc::branch(ir::BranchInst *inst, MachineBlock *block) {
  if (!inst->isConditional()) {
    auto dest = static_cast<ir::BasicBlock *>(inst->getOperand(0));
    block->pushInstruction(make_unique<Jump>(dest));
    return;
  }
  auto cond = inst->getOperand(0);
  auto trueBlock = static_cast<ir::BasicBlock *>(inst->getOperand(1));
  auto falseBlock = static_cast<ir::BasicBlock *>(inst->getOperand(2));
  MachineInst *condInst = nullptr;
  switch (cond->getValueKind()) {
  case ValueKind::Inst:
    condInst = _instMap[static_cast<ir::Instruction *>(cond)];
    break;
  case ValueKind::ConstNum:
    // TODO
    break;
  default:
    throw std::runtime_error("Invalid condition for branch instruction");
  }
  block->pushInstruction(
      make_unique<Jump>(condInst, MReg::zeroInst, trueBlock));
  block->pushInstruction(make_unique<Jump>(falseBlock));
}

} // namespace riscv

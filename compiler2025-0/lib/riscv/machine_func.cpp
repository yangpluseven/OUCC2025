#include "riscv/machine_func.h"
#include "riscv/mir_util.h"
#include "riscv/registers.h"

namespace riscv {

using ir::GlobalVariable;
using ir::InstKind;
using ir::Instruction;
using ir::ValueKind;
using std::make_unique;
using std::unique_ptr;

int MachineBlock::_counter = 0;

MachineBlock::MachineBlock() : BlockBase(_counter++) {}

MachineBlock::MachineBlock(int id) : BlockBase(id) { _counter = id + 1; }

MachineBlock::MachineBlock(std::string name) : BlockBase(-1), _name(name) {}

MachineInst *MachineBlock::pushMInst(std::unique_ptr<MachineInst> inst) {
  auto machineInst =
      static_cast<MachineInst *>(BlockBase::pushInstruction(std::move(inst)));
  return machineInst;
}

// Currently the name must match the original LLVM IR basicblock (ATTENTION)
std::string MachineBlock::getLabel() const {
  if (getID() == -1) {
    return "." + _name;
  }
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
  switch (operand1->getValueKind()) {
  case ValueKind::Arg:
    src1 = handleArg(static_cast<ir::Argument *>(operand1), block);
    break;
  case ValueKind::Inst:
    src1 = _instMap[static_cast<ir::Instruction *>(operand1)];
    break;
  }
  MachineInst *src2 = nullptr;
  switch (operand2->getValueKind()) {
  case ValueKind::Arg:
    src2 = handleArg(static_cast<ir::Argument *>(operand2), block);
    break;
  case ValueKind::Inst:
    src2 = _instMap[static_cast<ir::Instruction *>(operand2)];
    break;
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
  auto type = cond->getType();
  switch (cond->getValueKind()) {
  case ValueKind::Inst:
    condInst = _instMap[static_cast<ir::Instruction *>(cond)];
    break;
  case ValueKind::ConstNum:
    if (type->isF32()) {
      condInst = loadImmI(
          block, static_cast<ir::ConstantNumber *>(cond)->floatValue());
    } else {
      condInst =
          loadImmI(block, static_cast<ir::ConstantNumber *>(cond)->intValue());
    }
    break;
  default:
    throw std::runtime_error("Invalid condition for branch instruction");
  }
  block->pushInstruction(
      make_unique<Jump>(JumpOp::NE, condInst, MReg::zeroInst, trueBlock));
  block->pushInstruction(make_unique<Jump>(falseBlock));
}

int MachineFunc::call(ir::CallInst *inst, MachineBlock *block) {
  auto func = static_cast<ir::Function *>(inst->getOperand(0));
  int iSize = 0, fSize = 0;
  for (int i = 0; i < inst->getNumOperands(); i++) {
    auto param = inst->getOperand(i);
    bool isFloat = param->getType()->isF32();
    auto &callerRegs = isFloat ? MReg::fCallerRegs : MReg::iCallerRegs;
    auto &curSize = isFloat ? fSize : iSize;
    if (curSize < callerRegs.size()) {
      switch (param->getValueKind()) {
      case ValueKind::Arg: {
        auto tmp = handleArg(static_cast<ir::Argument *>(param), block);
        tmp->setDest(callerRegs[curSize]);
        break;
      }
      case ValueKind::Inst:
        block->pushMInst(
            make_unique<RR>(RROp::MV, callerRegs[curSize],
                            _instMap[static_cast<ir::Instruction *>(param)]));
        break;
      case ValueKind::ConstNum:
        if (isFloat) {
          auto tmp = loadImmF(
              block, static_cast<ir::ConstantNumber *>(param)->floatValue());
          tmp->setDest(callerRegs[curSize]);
        } else {
          auto tmp = loadImmI(
              block, static_cast<ir::ConstantNumber *>(param)->intValue());
          tmp->setDest(callerRegs[curSize]);
        }
        break;
      }
    } else {
      switch (param->getValueKind()) {
      case ValueKind::Arg: {
        auto tmp = handleArg(static_cast<ir::Argument *>(param), block);
        block->pushMInst(make_unique<StoreTo>(
            StoreItem::CALL_PARAM, tmp, MReg::argsStackOffset(iSize, fSize)));
        break;
      }
      case ValueKind::Inst:
        block->pushMInst(make_unique<StoreTo>(
            StoreItem::CALL_PARAM,
            _instMap[static_cast<ir::Instruction *>(param)],
            MReg::argsStackOffset(iSize, fSize)));
        break;
      case ValueKind::ConstNum: {
        auto constNum = static_cast<ir::ConstantNumber *>(param);
        MachineInst *tmp = nullptr;
        if (isFloat) {
          tmp = loadImmI(block, constNum->floatValue());
        } else {
          tmp = loadImmI(block, constNum->intValue());
        }
        block->pushMInst(make_unique<StoreTo>(
            StoreItem::CALL_PARAM, tmp, MReg::argsStackOffset(iSize, fSize)));
        break;
      }
      }
    }
    curSize++;
  }
  block->pushMInst(make_unique<Call>(func));
  if (inst->retTypeKind() != ir::BasicKind::VOID) {
    auto retType = inst->getType();
    MachineInst *retInst = nullptr;
    if (retType->isF32()) {
      retInst =
          block->pushMInst(make_unique<RR>(RROp::MV, MAKE_F32, MReg::fa0Inst));
    } else {
      retInst =
          block->pushMInst(make_unique<RR>(RROp::MV, MAKE_I32, MReg::a0Inst));
    }
    _instMap[inst] = retInst;
  }
  return inst->getNumOperands() - 1; // Return the number of parameters
}

void MachineFunc::gep(ir::GetElementPtrInst *inst, MachineBlock *block) {
  auto ptr = inst->getOperand(0);
  MachineInst *base = nullptr;
  MachineInst *mul1 = nullptr;
  std::pair<bool, int> offset;
  switch (ptr->getValueKind()) {
  case ValueKind::Global:
    base = block->pushMInst(
        make_unique<LLA>(MAKE_I32, static_cast<GlobalVariable *>(ptr)));
    mul1 = block->pushMInst(make_unique<LI>(
        MAKE_I32, inst->getType()->getBaseType()->getSize() / 8));
    break;
  case ValueKind::Arg: {
    offset = _argOffsets[static_cast<ir::Argument *>(ptr)];
    base = block->pushMInst(
        make_unique<LoadFrom>(offset.first ? LoadItem::INNER : LoadItem::OUTER,
                              MAKE_I32, offset.second));
    mul1 = block->pushMInst(make_unique<LI>(
        MAKE_I32, inst->getType()->getBaseType()->getSize() / 8));
    break;
  }
  case ValueKind::Inst: {
    if (inst->getNumOperands() == 3) {
      mul1 = block->pushMInst(make_unique<LI>(
          MAKE_I32,
          inst->getType()->getBaseType()->getBaseType()->getSize() / 8));
    } else {
      mul1 = block->pushMInst(make_unique<LI>(
          MAKE_I32, inst->getType()->getBaseType()->getSize() / 8));
    }
    auto pInst = static_cast<Instruction *>(ptr);
    if (pInst->getInstKind() == InstKind::Alloca) {
      int offset = _localOffsets[static_cast<ir::AllocaInst *>(pInst)];
      base = block->pushMInst(make_unique<LEA>(MAKE_I32, offset));
    } else {
      // Handle other cases
      base = _instMap[pInst];
    }
    break;
  }
  }
  auto operand = inst->getLastOperand();
  MachineInst *mul2 = nullptr;
  switch (operand->getValueKind()) {
  case ValueKind::Arg:
    mul2 = handleArg(static_cast<ir::Argument *>(operand), block);
    break;
  case ValueKind::Inst: {
    auto tmp = _instMap[static_cast<ir::Instruction *>(operand)];
    if (tmp->getDest()->getRegType()->getBasicKind() == ir::BasicKind::I32) {
      mul2 = tmp;
    } else {
      // Handle other cases, like F32
      mul2 = block->pushMInst(make_unique<RR>(RROp::MV, MAKE_I32, tmp));
    }
    break;
  }
  case ValueKind::ConstNum:
    if (operand->getType()->isF32()) {
      mul2 = loadImmI(block,
                      static_cast<ir::ConstantNumber *>(operand)->floatValue());
    } else {
      mul2 = loadImmI(block,
                      static_cast<ir::ConstantNumber *>(operand)->intValue());
    }
    break;
  default:
    throw std::runtime_error("Invalid operand for GEP instruction");
  }
  auto mulResult =
      block->pushMInst(make_unique<RRR>(RRROp::MUL, MAKE_I32, mul1, mul2));
  auto addResult =
      block->pushMInst(make_unique<RRR>(RRROp::ADD, MAKE_I32, base, mulResult));
  _instMap[inst] = addResult;
}

void MachineFunc::load(ir::LoadInst *inst, MachineBlock *block) {
  auto ptr = inst->getOperand(0);
  MachineInst *base = nullptr;
  int size = 4; // Default size
  switch (ptr->getValueKind()) {
  case ValueKind::Global:
    base = block->pushMInst(
        make_unique<LLA>(MAKE_I32, static_cast<GlobalVariable *>(ptr)));
    break;
  case ValueKind::Arg: {
    auto tmp = handleArg(static_cast<ir::Argument *>(ptr), block);
    _instMap[inst] = tmp;
    return;
  }
  case ValueKind::Inst: {
    auto pInst = static_cast<Instruction *>(ptr);
    size = pInst->getType()->getBaseType()->getSize() / 8;
    if (pInst->getInstKind() == InstKind::Alloca) {
      int offset = _localOffsets[static_cast<ir::AllocaInst *>(pInst)];
      base = block->pushMInst(make_unique<LEA>(MAKE_I32, offset));
    } else {
      // Handle other cases
      base = _instMap[pInst];
    }
    break;
  }
  }
  auto loadInst =
      block->pushMInst(make_unique<Load>(ptr->makeRegType(), base, 0, size));
  _instMap[inst] = loadInst;
}

void MachineFunc::ret(ir::RetInst *inst, MachineBlock *block,
                      ir::BasicBlock *exitBlock) {
  if (inst->empty()) {
    block->pushMInst(make_unique<Jump>(exitBlock));
    return;
  }
  auto retVal = inst->getOperand(0);
  MachineInst *retInst = nullptr;
  switch (retVal->getValueKind()) {
  case ValueKind::Arg:
    retInst = handleArg(static_cast<ir::Argument *>(retVal), block);
    break;
  case ValueKind::Inst:
    retInst = _instMap[static_cast<ir::Instruction *>(retVal)];
    break;
  case ValueKind::ConstNum:
    if (retVal->getType()->isF32()) {
      retInst = loadImmF(
          block, static_cast<ir::ConstantNumber *>(retVal)->floatValue());
    } else {
      retInst = loadImmI(block,
                         static_cast<ir::ConstantNumber *>(retVal)->intValue());
    }
    break;
  default:
    throw std::runtime_error("Invalid return value for Ret instruction");
  }
  if (retVal->getType()->isF32()) {
    block->pushMInst(make_unique<RR>(RROp::MV, MReg::fa0Inst, retInst));
  } else {
    block->pushMInst(make_unique<RR>(RROp::MV, MReg::a0Inst, retInst));
  }
  block->pushMInst(make_unique<Jump>(exitBlock));
}

void MachineFunc::store(ir::StoreInst *inst, MachineBlock *block) {
  auto value = inst->getOperand(0);
  auto ptr = inst->getOperand(1);
  MachineInst *base = nullptr;
  int size = 4; // Default size
  switch (ptr->getValueKind()) {
  case ValueKind::Global:
    base = block->pushMInst(
        make_unique<LLA>(MAKE_I32, static_cast<GlobalVariable *>(ptr)));
    break;
  case ValueKind::Arg: {
    base = handleArg(static_cast<ir::Argument *>(ptr), block);
    break;
  }
  case ValueKind::Inst: {
    auto pInst = static_cast<Instruction *>(ptr);
    size = pInst->getType()->getBaseType()->getSize() / 8;
    if (pInst->getInstKind() == InstKind::Alloca) {
      int offset = _localOffsets[static_cast<ir::AllocaInst *>(pInst)];
      base = block->pushMInst(make_unique<LEA>(MAKE_I32, offset));
    } else {
      // Handle other cases
      base = _instMap[pInst];
    }
    break;
  }
  }
  MachineInst *valueInst = nullptr;
  switch (value->getValueKind()) {
  case ValueKind::Arg:
    valueInst = handleArg(static_cast<ir::Argument *>(value), block);
    break;
  case ValueKind::Inst:
    valueInst = _instMap[static_cast<ir::Instruction *>(value)];
    break;
  case ValueKind::ConstNum:
    if (value->getType()->isF32()) {
      valueInst = loadImmI(
          block, static_cast<ir::ConstantNumber *>(value)->floatValue());
    } else {
      valueInst =
          loadImmI(block, static_cast<ir::ConstantNumber *>(value)->intValue());
    }
    break;
  default:
    throw std::runtime_error("Invalid value for Store instruction");
  }
  block->pushMInst(make_unique<Store>(valueInst, base, 0, size));
}

using ir::CmpOp;

void MachineFunc::icmp(ir::CmpInst *inst, MachineBlock *block) {
  auto operand1 = inst->getOperand(0);
  auto operand2 = inst->getOperand(1);
  MachineInst *src1 = nullptr;
  switch (operand1->getValueKind()) {
  case ValueKind::Arg:
    src1 = handleArg(static_cast<ir::Argument *>(operand1), block);
    break;
  case ValueKind::Inst:
    src1 = _instMap[static_cast<ir::Instruction *>(operand1)];
    break;
  case ValueKind::ConstNum:
    src1 = loadImmI(block,
                    static_cast<ir::ConstantNumber *>(operand1)->intValue());
    break;
  }
  MachineInst *src2 = nullptr;
  switch (operand2->getValueKind()) {
  case ValueKind::Arg:
    src2 = handleArg(static_cast<ir::Argument *>(operand2), block);
    break;
  case ValueKind::Inst:
    src2 = _instMap[static_cast<ir::Instruction *>(operand2)];
    break;
  case ValueKind::ConstNum:
    src2 = loadImmI(block,
                    static_cast<ir::ConstantNumber *>(operand2)->intValue());
    break;
  }
  MachineInst *tmp = nullptr;
  MachineInst *result = nullptr;
  switch (inst->getOp()) {
  case CmpOp::EQ:
    // Maybe eq is enough?
    tmp = block->pushMInst(make_unique<RRR>(RRROp::SUB, MAKE_I32, src1, src2));
    result =
        block->pushMInst(make_unique<RR>(RROp::SEQZ, MAKE_I32, src1, src2));
    break;
  case CmpOp::NE:
    tmp = block->pushMInst(make_unique<RRR>(RRROp::SUB, MAKE_I32, src1, src2));
    result =
        block->pushMInst(make_unique<RR>(RROp::SNEZ, MAKE_I32, src1, src2));
    break;
  case CmpOp::SGE:
    tmp = block->pushMInst(make_unique<RRR>(RRROp::SLT, MAKE_I32, src1, src2));
    result = block->pushMInst(make_unique<RRI>(RRIOp::XORI, MAKE_I32, src1, 1));
    break;
  case CmpOp::SGT:
    result =
        block->pushMInst(make_unique<RRR>(RRROp::SGT, MAKE_I32, src2, src1));
    break;
  case CmpOp::SLE:
    tmp = block->pushMInst(make_unique<RRR>(RRROp::SGT, MAKE_I32, src1, src2));
    result = block->pushMInst(make_unique<RRI>(RRIOp::XORI, MAKE_I32, src1, 1));
    break;
  case CmpOp::SLT:
    result =
        block->pushMInst(make_unique<RRR>(RRROp::SLT, MAKE_I32, src1, src2));
    break;
  default:
    throw std::runtime_error("Invalid comparison operation");
  }
  _instMap[inst] = result;
}

using ir::CmpOp;

void MachineFunc::fcmp(ir::CmpInst *inst, MachineBlock *block) {
  auto operand1 = inst->getOperand(0);
  auto operand2 = inst->getOperand(1);
  MachineInst *src1 = nullptr;
  switch (operand1->getValueKind()) {
  case ValueKind::Arg:
    src1 = handleArg(static_cast<ir::Argument *>(operand1), block);
    break;
  case ValueKind::Inst:
    src1 = _instMap[static_cast<ir::Instruction *>(operand1)];
    break;
  case ValueKind::ConstNum:
    src1 = loadImmF(block,
                    static_cast<ir::ConstantNumber *>(operand1)->floatValue());
    break;
  }
  MachineInst *src2 = nullptr;
  switch (operand2->getValueKind()) {
  case ValueKind::Arg:
    src2 = handleArg(static_cast<ir::Argument *>(operand2), block);
    break;
  case ValueKind::Inst:
    src2 = _instMap[static_cast<ir::Instruction *>(operand2)];
    break;
  case ValueKind::ConstNum:
    src2 = loadImmF(block,
                    static_cast<ir::ConstantNumber *>(operand2)->floatValue());
    break;
  }
  MachineInst *result = nullptr;
  if (inst->getOp() == CmpOp::UNE) {
    auto tmp =
        block->pushMInst(make_unique<RRR>(RRROp::EQ, MAKE_I32, src1, src2));
    result = block->pushMInst(make_unique<RRI>(RRIOp::XORI, MAKE_I32, tmp, 1));
    _instMap[inst] = result;
    return;
  }
  RRROp op;
  switch (inst->getOp()) {
  case CmpOp::OEQ:
    op = RRROp::EQ;
    break;
  case CmpOp::OGE:
    op = RRROp::GE;
    break;
  case CmpOp::OGT:
    op = RRROp::GT;
    break;
  case CmpOp::OLE:
    op = RRROp::LE;
    break;
  case CmpOp::OLT:
    op = RRROp::LT;
    break;
  default:
    throw std::runtime_error("Invalid floating-point comparison operation");
  }
  result = block->pushMInst(make_unique<RRR>(op, MAKE_I32, src1, src2));
  _instMap[inst] = result;
  return;
}

using ir::InstKind;

void MachineFunc::bitcast(ir::CastInst *inst, MachineBlock *block) {
  auto operand = static_cast<ir::Instruction *>(inst->getOperand(0));
  auto src = _instMap[operand];
  if (operand->getInstKind() == InstKind::Alloca) {
    src = block->pushMInst(make_unique<LEA>(
        MAKE_I32, _localOffsets[static_cast<ir::AllocaInst *>(operand)]));
  }
  auto result =
      block->pushMInst(make_unique<RR>(RROp::MV, inst->makeRegType(), src));
  _instMap[inst] = result;
}

void MachineFunc::zext(ir::CastInst *inst, MachineBlock *block) {
  auto operand = inst->getOperand(0);
  MachineInst *src = nullptr;
  switch (operand->getValueKind()) {
  case ValueKind::Arg:
    src = handleArg(static_cast<ir::Argument *>(operand), block);
    break;
  case ValueKind::Inst:
    src = _instMap[static_cast<ir::Instruction *>(operand)];
    break;
  case ValueKind::ConstNum:
    src =
        loadImmI(block, static_cast<ir::ConstantNumber *>(operand)->intValue());
    break;
  default:
    throw std::runtime_error("Invalid operand for zext instruction");
  }
  auto result =
      block->pushMInst(make_unique<RR>(RROp::MV, inst->makeRegType(), src));
  _instMap[inst] = result;
}

void MachineFunc ::sext(ir::CastInst *inst, MachineBlock *block) {
  auto operand = inst->getOperand(0);
  MachineInst *src = nullptr;
  switch (operand->getValueKind()) {
  case ValueKind::Arg:
    src = handleArg(static_cast<ir::Argument *>(operand), block);
    break;
  case ValueKind::Inst:
    src = _instMap[static_cast<ir::Instruction *>(operand)];
    break;
  case ValueKind::ConstNum:
    src =
        loadImmI(block, static_cast<ir::ConstantNumber *>(operand)->intValue());
    break;
  default:
    throw std::runtime_error("Invalid operand for sext instruction");
  }
  auto result =
      block->pushMInst(make_unique<RR>(RROp::NEG, inst->makeRegType(), src));
  _instMap[inst] = result;
}

void MachineFunc::fptosi(ir::CastInst *inst, MachineBlock *block) {
  auto operand = inst->getOperand(0);
  MachineInst *src = nullptr;
  switch (operand->getValueKind()) {
  case ValueKind::Arg:
    src = handleArg(static_cast<ir::Argument *>(operand), block);
    break;
  case ValueKind::Inst:
    src = _instMap[static_cast<ir::Instruction *>(operand)];
    break;
  case ValueKind::ConstNum:
    src = loadImmF(block,
                   static_cast<ir::ConstantNumber *>(operand)->floatValue());
    break;
  default:
    throw std::runtime_error("Invalid operand for fptosi instruction");
  }
  auto result =
      block->pushMInst(make_unique<RR>(RROp::CVT, inst->makeRegType(), src));
  _instMap[inst] = result;
}

void MachineFunc::sitofp(ir::CastInst *inst, MachineBlock *block) {
  auto operand = inst->getOperand(0);
  MachineInst *src = nullptr;
  switch (operand->getValueKind()) {
  case ValueKind::Arg:
    src = handleArg(static_cast<ir::Argument *>(operand), block);
    break;
  case ValueKind::Inst:
    src = _instMap[static_cast<ir::Instruction *>(operand)];
    break;
  case ValueKind::ConstNum:
    src =
        loadImmI(block, static_cast<ir::ConstantNumber *>(operand)->intValue());
    break;
  default:
    throw std::runtime_error("Invalid operand for sitofp instruction");
  }
  auto result =
      block->pushMInst(make_unique<RR>(RROp::CVT, inst->makeRegType(), src));
  _instMap[inst] = result;
}

void MachineFunc::move(ir::MoveInst *inst, MachineBlock *block) {
  // TODO MoveInst is used to handle phi nodes, which are not yet supported
}

} // namespace riscv

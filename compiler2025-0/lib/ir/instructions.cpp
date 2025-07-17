#include "ir/instructions.h"
#include "ir/function.h"
#include <cassert>
#include <sstream>

namespace ir {

//===---------------- Binary ----------------===//

std::string BinaryInst::opToString(BinaryOp op) {
  switch (op) {
  case BinaryOp::ADD:
    return "add";
  case BinaryOp::SUB:
    return "sub";
  case BinaryOp::MUL:
    return "mul";
  case BinaryOp::SDIV:
    return "sdiv";
  case BinaryOp::SREM:
    return "srem";
  case BinaryOp::XOR:
    return "xor";
  case BinaryOp::FADD:
    return "fadd";
  case BinaryOp::FSUB:
    return "fsub";
  case BinaryOp::FMUL:
    return "fmul";
  case BinaryOp::FDIV:
    return "fdiv";
  default:
    assert(false && "Unknown binary op");
  }
}

BinaryInst::BinaryInst(BinaryOp op, Value *lhs, Value *rhs, BasicBlock *block)
    : Instruction(lhs->getType()->clone(), {lhs, rhs}, block), _op(op) {
  assert(*lhs->getType() == *rhs->getType() &&
         "Operands must have the same type");
}

BinaryOp BinaryInst::getOp() const { return _op; }

InstKind BinaryInst::getInstKind() const { return InstKind::Binary; }

std::string BinaryInst::str() const {
  std::ostringstream oss;
  oss << getSSAName() << " = " << opToString(_op) << " " << getType()->str()
      << " " << getOperand(0)->str() << ", " << getOperand(1)->str();
  return oss.str();
}

std::unique_ptr<Instruction> BinaryInst::cloneEmpty() const {
  auto cloned = std::make_unique<BinaryInst>(getType()->clone(), nullptr, _op);
  cloned->_cloneTarget = const_cast<BinaryInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

//===---------------- Cmp ----------------===//

std::string CmpInst::opToString(CmpOp op) {
  switch (op) {
  case CmpOp::EQ:
    return "icmp eq";
  case CmpOp::NE:
    return "icmp ne";
  case CmpOp::SLT:
    return "icmp slt";
  case CmpOp::SGT:
    return "icmp sgt";
  case CmpOp::SLE:
    return "icmp sle";
  case CmpOp::SGE:
    return "icmp sge";
  case CmpOp::OEQ:
    return "fcmp oeq";
  case CmpOp::OLT:
    return "fcmp olt";
  case CmpOp::OGT:
    return "fcmp ogt";
  case CmpOp::OLE:
    return "fcmp ole";
  case CmpOp::OGE:
    return "fcmp oge";
  case CmpOp::UNE:
    return "fcmp une";
  default:
    assert(false && "Unknown cmp op");
  }
}

CmpInst::CmpInst(BasicBlock *block, CmpOp op, Value *lhs, Value *rhs)
    : Instruction(std::make_unique<BasicType>(BasicKind::I1), {lhs, rhs},
                  block),
      _op(op) {}

bool CmpInst::isICmpInst() const {
  switch (_op) {
  case CmpOp::EQ:
  case CmpOp::NE:
  case CmpOp::SLT:
  case CmpOp::SGT:
  case CmpOp::SLE:
  case CmpOp::SGE:
    return true;
  case CmpOp::OEQ:
  case CmpOp::OLT:
  case CmpOp::OGT:
  case CmpOp::OLE:
  case CmpOp::OGE:
  case CmpOp::UNE:
    return false;
  default:
    assert(false && "Unknown cmp op");
  }
}

CmpOp CmpInst::getOp() const { return _op; }

InstKind CmpInst::getInstKind() const { return InstKind::ICmp; }

std::string CmpInst::str() const {
  std::ostringstream oss;
  oss << getSSAName() << " = " << opToString(_op) << " "
      << getOperand(0)->getType()->str() << " " << getOperand(0)->str() << ", "
      << getOperand(1)->str();
  return oss.str();
}

std::unique_ptr<Instruction> CmpInst::cloneEmpty() const {
  auto cloned = std::make_unique<CmpInst>(nullptr, _op, nullptr, nullptr);
  cloned->_cloneTarget = const_cast<CmpInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

//===---------------- Cast ----------------===//

std::string CastInst::toString(CastOp op) {
  switch (op) {
  case CastOp::BitCast:
    return "bitcast";
  case CastOp::FPToSI:
    return "fptosi";
  case CastOp::SIToFP:
    return "sitofp";
  case CastOp::SExt:
    return "sext";
  case CastOp::ZExt:
    return "zext";
  default:
    assert(false && "Unknown cast op");
  }
}

CastInst::CastInst(std::unique_ptr<Type> targetType, BasicBlock *block,
                   CastOp op, Value *val)
    : Instruction(std::move(targetType), {val}, block), _op(op) {}

CastOp CastInst::getCastOp() const { return _op; }

InstKind CastInst::getInstKind() const {
  switch (_op) {
  case CastOp::BitCast:
    return InstKind::BitCast;
  case CastOp::FPToSI:
    return InstKind::FPToSI;
  case CastOp::SIToFP:
    return InstKind::SIToFP;
  case CastOp::SExt:
    return InstKind::SExt;
  case CastOp::ZExt:
    return InstKind::ZExt;
  default:
    assert(false && "Invalid cast op");
  }
}

std::string CastInst::str() const {
  std::ostringstream oss;
  oss << getSSAName() << " = " << toString(_op) << " "
      << getOperand(0)->getType()->str() << " " << getOperand(0)->str()
      << " to " << getType()->str();
  return oss.str();
}

std::unique_ptr<Instruction> CastInst::cloneEmpty() const {
  auto cloned =
      std::make_unique<CastInst>(getType()->clone(), nullptr, _op, nullptr);
  cloned->_cloneTarget = const_cast<CastInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

//===---------------- Terminator ----------------===//

RetInst::RetInst(BasicBlock *block, Value *retVal)
    : Instruction(std::make_unique<BasicType>(BasicKind::VOID), {retVal},
                  block) {}

InstKind RetInst::getInstKind() const { return InstKind::Ret; }

std::string RetInst::str() const {
  return "ret " + getOperand(0)->getType()->str() + " " + getOperand(0)->str();
}

std::unique_ptr<Instruction> RetInst::cloneEmpty() const {
  auto cloned = std::make_unique<RetInst>(nullptr, nullptr);
  cloned->_cloneTarget = const_cast<RetInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

BranchInst::BranchInst(BasicBlock *block, Value *cond, BasicBlock *trueBlock,
                       BasicBlock *falseBlock)
    : Instruction(std::make_unique<BasicType>(BasicKind::VOID), {cond}, block) {
  addOperand(trueBlock);
  addOperand(falseBlock);
}

BranchInst::BranchInst(BasicBlock *block, BasicBlock *target)
    : Instruction(std::make_unique<BasicType>(BasicKind::VOID), block) {
  addOperand(target);
}

InstKind BranchInst::getInstKind() const { return InstKind::Branch; }

std::string BranchInst::str() const {
  if (getNumOperands() == 1) {
    return "br label " + getOperand(0)->str();
  } else {
    return "br i1 " + getOperand(0)->str() + ", label " + getOperand(1)->str() +
           ", label " + getOperand(2)->str();
  }
}

std::unique_ptr<Instruction> BranchInst::cloneEmpty() const {
  auto cloned = std::make_unique<BranchInst>(nullptr, nullptr);
  cloned->_cloneTarget = const_cast<BranchInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

bool BranchInst::isTerminator() const { return true; }

//===---------------- Other Instructions ----------------===//

AllocaInst::AllocaInst(std::unique_ptr<Type> allocType, BasicBlock *block)
    : Instruction(std::make_unique<PointerType>(std::move(allocType)), block) {}

InstKind AllocaInst::getInstKind() const { return InstKind::Alloca; }

std::string AllocaInst::str() const {
  assert(getType()->isArray() || getType()->isPointer());
  return getSSAName() + " = alloca " + getType()->getBaseType()->str();
}

std::unique_ptr<Instruction> AllocaInst::cloneEmpty() const {
  auto cloned = std::make_unique<AllocaInst>(getType()->clone(), nullptr);
  cloned->_cloneTarget = const_cast<AllocaInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

LoadInst::LoadInst(std::unique_ptr<Type> loadedType, BasicBlock *block,
                   Value *ptr)
    : Instruction(std::move(loadedType), {ptr}, block) {}

InstKind LoadInst::getInstKind() const { return InstKind::Load; }

std::string LoadInst::str() const {
  return getSSAName() + " = load " + getType()->str() + ", " +
         getOperand(0)->getType()->str() + " " + getOperand(0)->str();
}

std::unique_ptr<Instruction> LoadInst::cloneEmpty() const {
  auto cloned =
      std::make_unique<LoadInst>(getType()->clone(), nullptr, nullptr);
  cloned->_cloneTarget = const_cast<LoadInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

StoreInst::StoreInst(BasicBlock *block, Value *val, Value *ptr)
    : Instruction(std::make_unique<BasicType>(BasicKind::VOID), {val, ptr},
                  block) {}

InstKind StoreInst::getInstKind() const { return InstKind::Store; }

std::string StoreInst::str() const {
  return "store " + getOperand(0)->getType()->str() + " " +
         getOperand(0)->str() + ", " + getOperand(1)->getType()->str() + " " +
         getOperand(1)->str();
}

std::unique_ptr<Instruction> StoreInst::cloneEmpty() const {
  auto cloned = std::make_unique<StoreInst>(nullptr, nullptr, nullptr);
  cloned->_cloneTarget = const_cast<StoreInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

GetElementPtrInst::GetElementPtrInst(std::unique_ptr<Type> resultType,
                                     BasicBlock *block, Value *base,
                                     const std::vector<Value *> &indices)
    : Instruction(std::move(resultType), {base}, block) {
  for (auto *idx : indices) {
    addOperand(idx);
  }
}

InstKind GetElementPtrInst::getInstKind() const { return InstKind::GEP; }

std::string GetElementPtrInst::str() const {
  std::ostringstream oss;
  oss << getSSAName() << " = getelementptr inbounds "
      << getOperand(0)->getType()->str() << ", "
      << getOperand(0)->getType()->str() << " " << getOperand(0)->str();
  for (size_t i = 1; i < getNumOperands(); ++i) {
    oss << ", " << getOperand(i)->getType()->str() << " "
        << getOperand(i)->str();
  }
  return oss.str();
}

std::unique_ptr<Instruction> GetElementPtrInst::cloneEmpty() const {
  auto cloned = std::make_unique<GetElementPtrInst>(
      getType()->clone(), nullptr, nullptr, std::vector<Value *>{});
  cloned->_cloneTarget = const_cast<GetElementPtrInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

CallInst::CallInst(BasicBlock *block, Function *func,
                   const std::vector<Value *> &args)
    : Instruction(func->getType()->clone(), args, block) {
  addOperand(func);
}

InstKind CallInst::getInstKind() const { return InstKind::Call; }

std::string CallInst::str() const {
  std::ostringstream oss;
  oss << getSSAName() << " = call " << getType()->str() << " "
      << getOperand(getNumOperands() - 1)->str() << "(";
  for (size_t i = 0; i < getNumOperands() - 1; ++i) {
    if (i > 0)
      oss << ", ";
    oss << getOperand(i)->getType()->str() << " " << getOperand(i)->str();
  }
  oss << ")";
  return oss.str();
}

std::unique_ptr<Instruction> CallInst::cloneEmpty() const {
  auto cloned =
      std::make_unique<CallInst>(nullptr, nullptr, std::vector<Value *>{});
  cloned->_cloneTarget = const_cast<CallInst *>(this);
  cloned->_notRemapped = true;
  return cloned;
}

} // namespace ir

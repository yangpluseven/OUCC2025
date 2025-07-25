#ifndef IR_INSTRUCTIONS_H
#define IR_INSTRUCTIONS_H

#include "ir/instruction.h"
#include <string>

namespace ir {

class Function;

//===---------------- Binary ----------------===//

enum class BinaryOp { ADD, SUB, MUL, SDIV, SREM, XOR, FADD, FSUB, FMUL, FDIV };

class BinaryInst : public Instruction {
private:
  BinaryOp _op;
  static std::string opToString(BinaryOp op);

public:
  BinaryInst(BasicBlock *block, BinaryOp op, Value *lhs, Value *rhs);
  BinaryInst(std::unique_ptr<Type> type, BasicBlock *block, BinaryOp op)
      : Instruction(std::move(type), block) {}

  BinaryOp getOp() const;
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

//===---------------- Cmp ----------------===//

enum class CmpOp {
  EQ, // Integer
  NE,
  SLT,
  SGT,
  SLE,
  SGE,
  OEQ, // Float
  OLT,
  OGT,
  OLE,
  OGE,
  UNE,
};

class CmpInst : public Instruction {
private:
  CmpOp _op;
  static std::string opToString(CmpOp op);

public:
  CmpInst(BasicBlock *block, CmpOp op, Value *lhs, Value *rhs);

  bool isICmpInst() const;
  CmpOp getOp() const;
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

//===---------------- Cast ----------------===//

enum class CastOp { BitCast, FPToSI, SIToFP, SExt, ZExt };

class CastInst : public Instruction {
private:
  CastOp _op;
  static std::string opToString(CastOp op);

public:
  CastInst(std::unique_ptr<Type> targetType, BasicBlock *block, CastOp op,
           Value *val);

  CastOp getCastOp() const;
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

//===---------------- Terminator ----------------===//

class RetInst : public Instruction {
public:
  RetInst(BasicBlock *block, Value *retVal);
  RetInst(BasicBlock *block);
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
  bool isTerminator() const override;
};

class BranchInst : public Instruction {
public:
  BranchInst(BasicBlock *block, Value *cond, BasicBlock *trueBlock,
             BasicBlock *falseBlock);
  BranchInst(BasicBlock *block, BasicBlock *target); // unconditional branch

  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
  bool isTerminator() const override;
};

//===---------------- Other Instructions ----------------===//

class AllocaInst : public Instruction {
public:
  AllocaInst(std::unique_ptr<Type> allocType, BasicBlock *block);
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

class LoadInst : public Instruction {
public:
  using Instruction::Instruction;
  LoadInst(BasicBlock *block, Value *ptr);
  LoadInst(std::unique_ptr<Type> loadedType, BasicBlock *block, Value *ptr);
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

class StoreInst : public Instruction {
public:
  StoreInst(BasicBlock *block, Value *val, Value *ptr);
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

class GetElementPtrInst : public Instruction {
private:
  static std::unique_ptr<Type> calcType(Value *value, size_t indexSize);

public:
  GetElementPtrInst(BasicBlock *block, Value *base,
                    const std::vector<Value *> &indices);
  GetElementPtrInst(std::unique_ptr<Type> targetType, BasicBlock *block);
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

class CallInst : public Instruction {
public:
  CallInst(BasicBlock *block, Function *func, const std::vector<Value *> &args);
  InstKind getInstKind() const override;
  std::string str() const override;
  std::unique_ptr<Instruction> cloneEmpty() const override;
};

} // namespace ir

#endif // IR_INSTRUCTIONS_H

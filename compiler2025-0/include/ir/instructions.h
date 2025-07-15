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
  static std::string toString(BinaryOp op);

public:
  BinaryInst(BinaryOp op, Type *type, BasicBlock *block)
      : Instruction(type, block) {}
  BinaryInst(BinaryOp op, Value *lhs, Value *rhs, BasicBlock *block);

  [[nodiscard]] BinaryOp getOp() const;
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
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
  static std::string toString(CmpOp op);

public:
  CmpInst(CmpOp op, Value *lhs, Value *rhs, BasicBlock *block);

  [[nodiscard]] CmpOp getCmpOp() const;
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

//===---------------- Cast ----------------===//

enum class CastOp { BitCast, FPToSI, SIToFP, SExt, ZExt };

class CastInst : public Instruction {
private:
  CastOp _op;
  static std::string toString(CastOp op);

public:
  CastInst(CastOp op, Value *val, Type *targetType, BasicBlock *block);

  [[nodiscard]] CastOp getCastOp() const;
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

//===---------------- Terminator ----------------===//

class RetInst : public Instruction {
public:
  explicit RetInst(Value *retVal, BasicBlock *block);
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

class BranchInst : public Instruction {
public:
  BranchInst(Value *cond, BasicBlock *trueBlock, BasicBlock *falseBlock,
             BasicBlock *block);
  BranchInst(BasicBlock *target, BasicBlock *block); // unconditional branch

  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
  [[nodiscard]] bool isTerminator() const override;
};

//===---------------- Other Instructions ----------------===//

class AllocaInst : public Instruction {
public:
  AllocaInst(Type *allocType, BasicBlock *block);
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

class LoadInst : public Instruction {
public:
  using Instruction::Instruction;
  LoadInst(Value *ptr, Type *loadedType, BasicBlock *block);
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

class StoreInst : public Instruction {
public:
  StoreInst(Value *val, Value *ptr, BasicBlock *block);
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

class GetElementPtrInst : public Instruction {
public:
  GetElementPtrInst(Value *base, const std::vector<Value *> &indices,
                    Type *resultType, BasicBlock *block);
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

class CallInst : public Instruction {
public:
  CallInst(Function *func, const std::vector<Value *> &args, BasicBlock *block);
  [[nodiscard]] InstKind kind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Instruction *clone() const override;
};

} // namespace ir

#endif // IR_INSTRUCTIONS_H

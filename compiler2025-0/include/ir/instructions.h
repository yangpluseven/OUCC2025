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
  BinaryInst(std::unique_ptr<Type> type, BasicBlock *block, BinaryOp op)
      : Instruction(std::move(type), block) {}
  BinaryInst(BinaryOp op, Value *lhs, Value *rhs, BasicBlock *block);

  [[nodiscard]] BinaryOp getOp() const;
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
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

  [[nodiscard]] bool isICmpInst() const;
  [[nodiscard]] CmpOp getOp() const;
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

//===---------------- Cast ----------------===//

enum class CastOp { BitCast, FPToSI, SIToFP, SExt, ZExt };

class CastInst : public Instruction {
private:
  CastOp _op;
  static std::string toString(CastOp op);

public:
  CastInst(std::unique_ptr<Type> targetType, BasicBlock *block, CastOp op,
           Value *val);

  [[nodiscard]] CastOp getCastOp() const;
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

//===---------------- Terminator ----------------===//

class RetInst : public Instruction {
public:
  explicit RetInst(BasicBlock *block, Value *retVal);
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

class BranchInst : public Instruction {
public:
  BranchInst(BasicBlock *block, Value *cond, BasicBlock *trueBlock,
             BasicBlock *falseBlock);
  BranchInst(BasicBlock *block, BasicBlock *target); // unconditional branch

  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
  [[nodiscard]] bool isTerminator() const override;
};

//===---------------- Other Instructions ----------------===//

class AllocaInst : public Instruction {
public:
  AllocaInst(BasicBlock *block, std::unique_ptr<Type> allocType);
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

class LoadInst : public Instruction {
public:
  using Instruction::Instruction;
  LoadInst(BasicBlock *block, std::unique_ptr<Type> loadedType, Value *ptr);
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

class StoreInst : public Instruction {
public:
  StoreInst(BasicBlock *block, Value *val, Value *ptr);
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

class GetElementPtrInst : public Instruction {
public:
  GetElementPtrInst(std::unique_ptr<Type> resultType, BasicBlock *block,
                    Value *base, const std::vector<Value *> &indices);
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

class CallInst : public Instruction {
public:
  CallInst(BasicBlock *block, Function *func, const std::vector<Value *> &args);
  [[nodiscard]] InstKind getInstKind() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Instruction> cloneEmpty() const override;
};

} // namespace ir

#endif // IR_INSTRUCTIONS_H

#ifndef RISCV_MACHINE_INST_H
#define RISCV_MACHINE_INST_H

#include "ir/global_variable.h"
#include "ir/instruction.h"
#include "ir/register.h"
#include "ir/type.h"
#include "riscv/machine_func.h"

#define MAKE_VOID std::make_unique<ir::BasicType>(ir::BasicKind::VOID)

namespace riscv {

class MachineBlock;

enum class MInstKind {
  Fake,
  LEA,
  Jump,
  Call,
  LI,
  LLA,
  LoadFrom,
  Load,
  RR,
  RRI,
  RRR,
  StoreTo,
  Store
};

enum class RRIOp { ADDI, ANDI, SLLIW, SRAIW, SRLI, SRLIW, XORI, SLTI };

enum class RROp { CVT, FABS, MV, NEG, SEQZ, SNEZ };

enum class RRROp {
  ADD,
  ADDW,
  SUB,
  SUBW,
  MUL,
  MULW,
  DIV,
  DIVW,
  REMW,
  EQ,
  GE,
  GT,
  LE,
  LT,
  AND,
  XOR,
  SLT,
  SGT
};

enum class LoadItem { SPILL, INNER, OUTER, LOCAL };

class MachineInst : public ir::InstBase {
private:
  static int _counter;
  ir::Reg *_dest = nullptr;

public:
  MachineInst(std::unique_ptr<ir::Type> type);

  MachineInst(std::unique_ptr<ir::Type> type,
              const std::vector<Value *> &useOperands);

  MachineInst(ir::Reg *dest)
      : InstBase(dest->getRegType()->clone(), _counter++), _dest(dest) {}

  MachineInst(ir::Reg *dest, const std::vector<Value *> &useOperands)
      : InstBase(dest->getRegType()->clone(), useOperands, _counter++),
        _dest(dest) {}

  MachineInst() : InstBase(MAKE_VOID, _counter++) {}

  virtual ~MachineInst() = default;

  // Get the dest register's name, virtual or real
  std::string getName() const override;

  ir::ValueKind getValueKind() const override {
    return ir::ValueKind::MachineInst;
  }

  ir::BasicKind getBasicKind() const {
    return static_cast<ir::BasicType *>(getType())->getBasicKind();
  }

  ir::Reg *getDest() const { return _dest; }

  void setDest(ir::Reg *dest) { _dest = dest; }

  ir::Reg *getSrc(size_t index) const {
    return static_cast<MachineInst *>(getOperand(index))->getDest();
  }

  std::vector<ir::Reg *> getRegs() const;

  virtual std::vector<ir::Reg *> getRead() const {
    std::vector<ir::Reg *> vec;
    for (size_t i = 0; i < getNumOperands(); i++) {
      auto inst = static_cast<MachineInst *>(getOperand(i));
      vec.push_back(inst->getDest());
    }
    return vec;
  }

  virtual std::vector<ir::Reg *> getWrite() const {
    if (_dest) {
      return {_dest};
    }
    return {};
  }

  virtual MInstKind getMInstKind() const { return MInstKind::Fake; }

  virtual void spill(ir::Reg *spilledReg, int offset, MachineBlock *block);
};

class ImmInst : public MachineInst {
private:
  int _imm;

public:
  ImmInst(std::unique_ptr<ir::Type> type, int imm)
      : MachineInst(std::move(type)), _imm(imm) {}

  ImmInst(std::unique_ptr<ir::Type> type,
          const std::vector<Value *> &useOperands, int imm)
      : MachineInst(std::move(type), useOperands), _imm(imm) {}

  ImmInst(ir::Reg *dest, int imm) : MachineInst(dest), _imm(imm) {}

  ImmInst(ir::Reg *dest, const std::vector<Value *> &useOperands, int imm)
      : MachineInst(dest, useOperands), _imm(imm) {}

  int getImm() const { return _imm; }
};

class LEA : public ImmInst {
public:
  LEA(std::unique_ptr<ir::Type> type, int imm)
      : ImmInst(std::move(type), imm) {}

  LEA(ir::Reg *dest, int imm) : ImmInst(dest, imm) {}

  MInstKind getMInstKind() const override { return MInstKind::LEA; }

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    return "add\t" + getDest()->str() + ", $local, #" +
           std::to_string(getImm());
  }
};

enum class JumpOp { NUL, EQ, NE, LT, LE, GT, GE };

class Jump : public MachineInst {
private:
  JumpOp _op = JumpOp::NUL;
  ir::BasicBlock *_target;

  std::string opToString() const {
    switch (_op) {
    case JumpOp::NUL:
      return "{null}";
    case JumpOp::EQ:
      return "eq";
    case JumpOp::NE:
      return "ne";
    case JumpOp::LT:
      return "lt";
    case JumpOp::LE:
      return "le";
    case JumpOp::GT:
      return "gt";
    case JumpOp::GE:
      return "ge";
    default:
      return "{unknown}";
    }
  }

public:
  Jump(JumpOp op, MachineInst *src0, MachineInst *src1, ir::BasicBlock *target)
      : MachineInst(MAKE_VOID, {src0, src1}), _op(op), _target(target) {}

  Jump(ir::BasicBlock *target) : _target(target) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  bool hasCond() const { return _op != JumpOp::NUL; }

  std::string str() const override {
    if (!hasCond()) {
      return "j\t." + _target->getLabel();
    }
    return "b" + opToString() + "\t" + getSrc(0)->str() + ", " +
           getSrc(1)->str() + ", ." + _target->getLabel();
  }
};

class Call : public MachineInst {
private:
  ir::Function *_func;

public:
  Call(ir::Function *func) : _func(func) {}

  std::vector<ir::Reg *> getRead() const override;

  std::vector<ir::Reg *> getWrite() const override;

  std::string str() const override { return "call\t" + _func->getRawName(); }
};

class LI : public ImmInst {
public:
  LI(std::unique_ptr<ir::Type> type, int imm) : ImmInst(std::move(type), imm) {}

  LI(ir::Reg *dest, int imm) : ImmInst(dest, imm) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    return "li\t" + getDest()->str() + ", " + std::to_string(getImm());
  }
};

class LLA : public MachineInst {
private:
  ir::GlobalVariable *_global;

public:
  LLA(std::unique_ptr<ir::Type> type, ir::GlobalVariable *global)
      : MachineInst(std::move(type)), _global(global) {}

  LLA(ir::Reg *dest, ir::GlobalVariable *global)
      : MachineInst(dest), _global(global) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    return "lla\t" + getDest()->str() + ", " + _global->getRawName();
  }
};

class LoadFrom : public ImmInst {
private:
  LoadItem _item;

  std::string itemToString() const noexcept {
    switch (_item) {
    case LoadItem::SPILL:
      return "spill";
    case LoadItem::INNER:
      return "inner";
    case LoadItem::OUTER:
      return "outer";
    case LoadItem::LOCAL:
      return "local";
    default:
      return "incomplete{LoadFrom.itemToString}";
    }
  }

public:
  LoadFrom(LoadItem item, std::unique_ptr<ir::Type> type, int imm)
      : ImmInst(std::move(type), imm), _item(item) {}

  LoadFrom(LoadItem item, ir::Reg *dest, int imm)
      : ImmInst(dest, imm), _item(item) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    return "load\t" + getDest()->str() + ", " + std::to_string(getImm()) +
           "($" + itemToString() + ")";
  }
};

class Load : public ImmInst {
private:
  int _size;

public:
  Load(std::unique_ptr<ir::Type> type, MachineInst *src, int imm, int size)
      : ImmInst(std::move(type), {src}, imm), _size(size) {}

  Load(ir::Reg *dest, MachineInst *src, int imm, int size)
      : ImmInst(dest, {src}, imm), _size(size) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    // TODO
    return "";
  }
};

class RR : public MachineInst {
private:
  RROp _op;

  std::string opToString() const noexcept {
    switch (_op) {
    case RROp::CVT:
      return "cvt";
    case RROp::FABS:
      return "fabs";
    case RROp::MV:
      return "mv";
    case RROp::NEG:
      return "neg";
    case RROp::SEQZ:
      return "seqz";
    case RROp::SNEZ:
      return "snez";
    default:
      return "incomplete{RR.opToString}";
    }
  }

public:
  RR(RROp op, std::unique_ptr<ir::Type> type, MachineInst *src)
      : MachineInst(std::move(type), {src}), _op(op) {}

  RR(RROp op, ir::Reg *dest, MachineInst *src)
      : MachineInst(dest, {src}), _op(op) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    // TODO
    return "";
  }
};

class RRI : public ImmInst {
private:
  RRIOp _op;

  std::string opToString() const noexcept {
    switch (_op) {
    case RRIOp::ADDI:
      return "addi";
    case RRIOp::ANDI:
      return "andi";
    case RRIOp::SLLIW:
      return "slliw";
    case RRIOp::SRAIW:
      return "sraiw";
    case RRIOp::SRLIW:
      return "srliw";
    case RRIOp::SRLI:
      return "srli";
    case RRIOp::XORI:
      return "xori";
    case RRIOp::SLTI:
      return "slti";
    default:
      return "incomplete{RRI.opToString}";
    }
  }

public:
  RRI(RRIOp op, std::unique_ptr<ir::Type> type, MachineInst *src, int imm)
      : ImmInst(std::move(type), {src}, imm), _op(op) {}

  RRI(RRIOp op, ir::Reg *dest, MachineInst *src, int imm)
      : ImmInst(dest, {src}, imm), _op(op) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    return opToString() + "\t" + getDest()->str() + ", " + getSrc(0)->str() +
           ", " + std::to_string(getImm());
  }
};

class RRR : public MachineInst {
private:
  RRROp _op;

  std::string opToString() const noexcept {
    switch (_op) {
    case RRROp::ADD:
      return "add";
    case RRROp::ADDW:
      return "addw";
    case RRROp::SUB:
      return "sub";
    case RRROp::SUBW:
      return "subw";
    case RRROp::MUL:
      return "mul";
    case RRROp::MULW:
      return "mulw";
    case RRROp::DIV:
      return "div";
    case RRROp::DIVW:
      return "divw";
    case RRROp::REMW:
      return "remw";
    case RRROp::EQ:
      return "eq";
    case RRROp::GE:
      return "ge";
    case RRROp::GT:
      return "gt";
    case RRROp::LE:
      return "le";
    case RRROp::LT:
      return "lt";
    case RRROp::AND:
      return "and";
    case RRROp::XOR:
      return "xor";
    case RRROp::SLT:
      return "slt";
    case RRROp::SGT:
      return "sgt";
    default:
      return "incomplete{RRR.opToString}";
    }
  }

public:
  RRR(RRROp op, std::unique_ptr<ir::Type> type, MachineInst *src0,
      MachineInst *src1)
      : MachineInst(std::move(type), {src0, src1}), _op(op) {}

  RRR(RRROp op, ir::Reg *dest, MachineInst *src0, MachineInst *src1)
      : MachineInst(dest, {src0, src1}), _op(op) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    // TODO
    return "";
  }
};

enum class StoreItem { LOCAL, CALL_PARAM, INNER_PARAM, OUTER_PARAM, SPILL };

class StoreTo : public ImmInst {
private:
  StoreItem _item;

  std::string itemToString() const noexcept {
    switch (_item) {
    case StoreItem::LOCAL:
      return "local";
    case StoreItem::CALL_PARAM:
      return "param_call";
    case StoreItem::INNER_PARAM:
      return "param_inner";
    case StoreItem::OUTER_PARAM:
      return "param_outer";
    case StoreItem::SPILL:
      return "spill";
    default:
      return "incomplete{StoreTo.itemToString}";
    }
  }

public:
  StoreTo(StoreItem item, MachineInst *src, int imm)
      : ImmInst(MAKE_VOID, {src}, imm), _item(item) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    return "store\t" + getSrc(0)->str() + ", " + std::to_string(getImm()) +
           "($" + itemToString() + ")";
  }
};

class Store : public ImmInst {
private:
  int _size;

public:
  Store(MachineInst *src0, MachineInst *src1, int imm, int size)
      : ImmInst(MAKE_VOID, {src0, src1}, imm), _size(size) {}

  void spill(ir::Reg *spilledReg, int offset, MachineBlock *block) override;

  std::string str() const override {
    // TODO
    return "";
  }
};

} // namespace riscv

#undef MAKE_VOID
#endif

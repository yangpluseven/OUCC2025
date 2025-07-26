#ifndef RISCV_MACHINE_INST_H
#define RISCV_MACHINE_INST_H

#include "ir/global_variable.h"
#include "ir/instruction.h"
#include "ir/register.h"
#include "ir/type.h"
#include "riscv/machine_func.h"

#define MAKE_VOID std::make_unique<ir::BasicType>(ir::BasicKind::VOID)

namespace riscv {

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

class MachineInst : public ir::InstBase {
private:
  static int _counter;
  ir::Reg *_dest = nullptr;

public:
  MachineInst(std::unique_ptr<ir::Type> type);
  MachineInst(std::unique_ptr<ir::Type> type,
              const std::vector<Value *> &useOperands);
  MachineInst(ir::Reg *dest);
  MachineInst();

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
  virtual void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) {
    return;
  }
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

  int getImm() const { return _imm; }
};

class LEA : public ImmInst {

public:
  using ImmInst::ImmInst;
  MInstKind getMInstKind() const override { return MInstKind::LEA; }
  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
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

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;

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

  std::vector<Reg *> getRead() const override {
    // TODO
    return {};
  }

  std::vector<Reg *> getWrite() const override {
    // TODO
    return {};
  }

  std::string str() const override { return "call\t" + _func->getRawName(); }
};

class LI : public ImmInst {
  using ImmInst::ImmInst;
  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
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

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
  std::string str() const override {
    return "lla\t" + getDest()->str() + ", " + _global->getRawName();
  }
};

enum class LoadItem { SPILL, INNER, OUTER, LOCAL };

class LoadFrom : public ImmInst {
private:
  LoadItem _item;

  std::string itemToString() const {
    // TODO
    return "";
  }

public:
  LoadFrom(LoadItem item, std::unique_ptr<ir::Type> type, int imm)
      : ImmInst(std::move(type), imm), _item(item) {}

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
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

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
  std::string str() const override;
};

enum class RROp { CVT, FABS, MV, NEG, SEQZ, SNEZ };

class RR : public MachineInst {
private:
  RROp _op;
  std::string opToString() const {
    // TODO
    return "";
  }

public:
  RR(RROp op, std::unique_ptr<ir::Type> type, MachineInst *src)
      : MachineInst(std::move(type), {src}), _op(op) {}

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
  std::string str() const override;
};

enum class RRIOp { ADDI, ANDI, SLLIW, SRAIW, SRLI, SRLIW, XORI, SLTI };

class RRI : public ImmInst {
private:
  RRIOp _op;
  std::string opToString() const {
    // TODO
    return " ";
  }

public:
  RRI(RRIOp op, std::unique_ptr<ir::Type> type, MachineInst *src, int imm)
      : ImmInst(std::move(type), {src}, imm), _op(op) {}

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
  std::string str() const override {
    return opToString() + "\t" + getDest()->str() + ", " + getSrc(0)->str() +
           ", " + std::to_string(getImm());
  }
};

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

class RRR : public MachineInst {
private:
  RRROp _op;
  std::string opToString() const {
    // TODO
    return "";
  }

public:
  RRR(RRROp op, std::unique_ptr<ir::Type> type, MachineInst *src0,
      MachineInst *src1)
      : MachineInst(std::move(type), {src0, src1}), _op(op) {}

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
  std::string str() const override;
};

enum class StoreItem { LOCAL, CALL_PARAM, INNER_PARAM, OUTER_PARAM, SPILL };

class StoreTo : public ImmInst {
private:
  StoreItem _item;
  std::string itemToString() const {
    // TODO
    return "";
  }

public:
  StoreTo(StoreItem item, MachineInst *src, int imm)
      : ImmInst(MAKE_VOID, {src}, imm), _item(item) {}

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
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

  void spill(ir::Reg *spilledReg, int offset, ir::BlockBase *block) override;
  std::string str() const override;
};

} // namespace riscv

#undef MAKE_VOID
#endif
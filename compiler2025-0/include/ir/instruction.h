#ifndef IR_INSTRUCTION_H
#define IR_INSTRUCTION_H

#include "ir/basic_block.h"
#include "ir/user.h"
#include "ir/value.h"
#include <string>
#include <unordered_map>

namespace ir {

class BasicBlock;

enum class InstKind {
  Alloca,
  Binary,
  BitCast,
  Branch,
  Call,
  FCmp,
  FPToSI,
  GEP,
  ICmp,
  Load,
  Phi,
  Ret,
  SExt,
  SIToFP,
  Store,
  ZExt,
};

class Instruction : public User {
private:
  static int _counter;
  int _id;
  int _indexInBlock;
  BasicBlock *_block;
  bool _notRemapped = false;

protected:
  Instruction(Type *type, BasicBlock *block) : User(type), _block(block) {}
  Instruction(Type *type, const std::vector<Value *> &useOperands,
              BasicBlock *block);

public:
  virtual ~Instruction() = default;

  [[nodiscard]] BasicBlock *getBlock() const { return _block; }
  // Used in optimization mostly
  void setBlock(BasicBlock *block) { _block = block; }

  [[nodiscard]] virtual std::string str() const = 0;
  [[nodiscard]] int getID() const { return _id; }
  // Get the SSA name like %1, %2
  [[nodiscard]] virtual std::string getSSAName() const;
  [[nodiscard]] std::string getName() const override;

  [[nodiscard]] virtual InstKind kind() const = 0;

  using ValueMap = std::unordered_map<ir::Value *, ir::Value *>;

  // Create a copy with old operands, notRemapped <- true
  virtual Instruction *clone() const = 0;
  virtual void remapOperands(const ValueMap &map);

  [[nodiscard]] bool isRemapped() const { return !_notRemapped; }
  [[nodiscard]] virtual bool isTerminator() const { return false; }
};

} // namespace ir

#endif // IR_INSTRUCTION_H
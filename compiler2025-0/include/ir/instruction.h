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
  int _indexInBlock = -1;
  bool _notRemapped = false;
  BasicBlock *_block;
  // Only used during clone process
  Instruction *_cloneTarget = nullptr;

protected:
  Instruction(Type *type, BasicBlock *block);
  Instruction(Type *type, const std::vector<Value *> &useOperands,
              BasicBlock *block);

public:
  virtual ~Instruction() = default;

  [[nodiscard]] BasicBlock *getBlock() const { return _block; }
  // Used in optimization mostly
  void setBlock(BasicBlock *block) { _block = block; }

  [[nodiscard]] int getID() const { return _id; }
  // Get the SSA name like %1, %2
  [[nodiscard]] virtual std::string getSSAName() const;
  // Get the LLVM .ll format instruction string
  [[nodiscard]] std::string str() const;

  [[nodiscard]] virtual InstKind kind() const = 0;

  using ValueMap = std::unordered_map<ir::Value *, ir::Value *>;

  // Create a copy without operands, notRemapped <- true
  virtual Instruction *clone() const = 0;
  // Use _cloneTarget to find the old instruction, use the map oldVal -> newVal
  // to map the operands. Set _cloneTarget to nullptr after the process
  virtual void remapOperands(const ValueMap &map);

  [[nodiscard]] bool isRemapped() const { return !_notRemapped; }
  [[nodiscard]] virtual bool isTerminator() const { return false; }
};

} // namespace ir

#endif // IR_INSTRUCTION_H
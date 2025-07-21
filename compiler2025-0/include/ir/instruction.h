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
  BasicBlock *_block;

protected:
  // Only used during clone process
  Instruction *_cloneTarget = nullptr;
  bool _notRemapped = false;
  Instruction(std::unique_ptr<Type> type, BasicBlock *block);
  Instruction(std::unique_ptr<Type> type,
              const std::vector<Value *> &useOperands, BasicBlock *block);

public:
  virtual ~Instruction() = default;

  ValueKind getValueKind() const override { return ValueKind::Inst; }

  [[nodiscard]] BasicBlock *getBlock() const { return _block; }
  // Used in optimization mostly
  void setBlock(BasicBlock *block) { _block = block; }

  [[nodiscard]] int getID() const { return _id; }
  // Get the SSA name like %v1, %v2
  [[nodiscard]] std::string getSSAName() const override;
  // Get the LLVM .ll format instruction string
  [[nodiscard]] std::string str() const;

  [[nodiscard]] virtual InstKind getInstKind() const = 0;

  using ValueMap = std::unordered_map<ir::Value *, ir::Value *>;

  // Create a empty copy without operands, set notRemapped to true. Other part
  // should be the same as the clone target
  virtual std::unique_ptr<Instruction> cloneEmpty() const = 0;
  // Use _cloneTarget to find the old instruction, use the map oldVal -> newVal
  // to map the operands. Set _cloneTarget to nullptr after the process
  // and set notRemapped to false
  void remapValues(const ValueMap &map);

  [[nodiscard]] bool isRemapped() const { return !_notRemapped; }
  [[nodiscard]] virtual bool isTerminator() const { return false; }
};

} // namespace ir

#endif // IR_INSTRUCTION_H
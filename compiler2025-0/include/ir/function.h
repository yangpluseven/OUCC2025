#ifndef IR_FUNCTION_H
#define IR_FUNCTION_H

#include "ir/basic_block.h"
#include "ir/value.h"
#include <memory>
#include <string>
#include <vector>

namespace ir {

class BasicBlock;
class Argument : public Value {
private:
  const std::string _name;

public:
  Argument(std::unique_ptr<Type> type, std::string name)
      : Value(std::move(type)), _name(std::move(name)) {}
  ValueKind getValueKind() const override { return ValueKind::Arg; }
  // Get the LLVM like SSA name, example: %a
  std::string getSSAName() const;
  // Get the LLVM like full name, example: i32 %a
  std::string str() const override;
};

class Function : public Value {
private:
  std::string _name;
  std::vector<std::unique_ptr<Argument>> _args;
  std::vector<std::unique_ptr<BasicBlock>> _blocks;

public:
  Function(std::unique_ptr<Type> type, std::string name)
      : Value(std::move(type)), _name(std::move(name)) {}

  ValueKind getValueKind() const { return ValueKind::Function; }

  [[nodiscard]] bool empty() const { return _blocks.empty(); }

  void addArg(std::unique_ptr<Argument> arg);
  // Return a viewport instead of the actual ownership
  [[nodiscard]] std::vector<Argument *> getArgs() const;

  void pushBlock(std::unique_ptr<BasicBlock> block);
  std::unique_ptr<BasicBlock> eraseBlock(size_t index);

  [[nodiscard]] BasicBlock *getBlock(size_t index) const;
  [[nodiscard]] BasicBlock *getEntryBlock() const;
  [[nodiscard]] size_t size() const { return _blocks.size(); }

  // Get the function's name
  std::string getRawName() const;
  // Form the .ll IR string for the whole block, call block->str() for the
  // block's .ll IR string including the label and all instructions
  std::string str() const override;

  using iterator = std::vector<std::unique_ptr<BasicBlock>>::iterator;
  using const_iterator =
      std::vector<std::unique_ptr<BasicBlock>>::const_iterator;

  BasicBlock *getBlock(iterator pos) const;
  // Insert using iterator, can be used in other insert functions
  iterator insertBlock(iterator pos, std::unique_ptr<BasicBlock> block);
  // Erase using iterator, move out the ownership
  std::unique_ptr<BasicBlock> eraseBlock(iterator pos);

  void insertBlockAfter(BasicBlock *target, std::unique_ptr<BasicBlock> block);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};

} // namespace ir

#endif // IR_FUNCTION_H

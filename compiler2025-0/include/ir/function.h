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
  Argument(Type *type, std::string name)
      : Value(type), _name(std::move(name)) {}
  std::string str() const override;
};

class Function : public Value {
private:
  std::string _name;
  std::vector<std::unique_ptr<Argument>> _args;
  std::vector<std::unique_ptr<BasicBlock>> _blocks;
  bool _canInline = false;

public:
  Function(Type *type, std::string name);

  [[nodiscard]] bool canInline() const { return _canInline; }
  [[nodiscard]] bool isDeclare() const;

  void addArg(std::unique_ptr<Argument> arg);
  [[nodiscard]] const std::vector<std::unique_ptr<Argument>> &getArgs() const;

  void pushBlock(std::unique_ptr<BasicBlock> block);
  std::unique_ptr<BasicBlock> eraseBlock(size_t index);

  [[nodiscard]] BasicBlock *getBlock(size_t index) const;
  [[nodiscard]] BasicBlock *getFirstBlock() const;
  [[nodiscard]] BasicBlock *getLastBlock() const;
  [[nodiscard]] size_t size() const { return _blocks.size(); }

  std::string getRawName() const;
  std::string str() const override;

  using iterator = std::vector<std::unique_ptr<BasicBlock>>::iterator;
  using const_iterator =
      std::vector<std::unique_ptr<BasicBlock>>::const_iterator;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};

} // namespace ir

#endif // IR_FUNCTION_H

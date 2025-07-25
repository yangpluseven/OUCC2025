#ifndef IR_BASIC_BLOCK_H
#define IR_BASIC_BLOCK_H

#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/value.h"
#include <string>
#include <vector>

namespace ir {

class Function;
class InstBase;

class BasicBlock : public Value {
private:
  static int _counter;
  int _id;
  Function *_function;
  std::vector<std::unique_ptr<InstBase>> _instructions;

public:
  explicit BasicBlock(Function *func);
  ValueKind getValueKind() const override { return ValueKind::Block; }
  Function *getFunction() const { return _function; }

  bool empty() const { return _instructions.empty(); }
  // Check the last instruction
  bool hasTerminator() const;
  void pushInstruction(std::unique_ptr<InstBase> inst);
  InstBase *getTerminator() const;
  InstBase *getInstruction(size_t index) const;
  void insertInstruction(size_t index, std::unique_ptr<InstBase> inst);
  std::unique_ptr<InstBase> eraseInstruction(size_t index);
  size_t size() const { return _instructions.size(); }

  // Get the LLVM like block label, example: bb0 bb1
  std::string getLabel() const;
  std::string getName() const { return "%" + getLabel(); }
  // Form the .ll IR string for the whole block, including the label and string
  // for all instructions
  std::string str() const override;

  using iterator = std::vector<std::unique_ptr<InstBase>>::iterator;
  using const_iterator = std::vector<std::unique_ptr<InstBase>>::const_iterator;

  InstBase *getInstruction(iterator pos) const;
  // Insert using iterator, can be used in other insert functions
  iterator insertInstruction(iterator pos, std::unique_ptr<InstBase> inst);
  // Erase using iterator, move out the ownership
  std::unique_ptr<InstBase> eraseInstruction(iterator pos);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};

} // namespace ir

#endif // IR_BASIC_BLOCK_H
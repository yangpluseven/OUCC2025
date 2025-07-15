#ifndef IR_BASIC_BLOCK_H
#define IR_BASIC_BLOCK_H

#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/value.h"
#include <string>
#include <vector>

namespace ir {

class Function;
class Instruction;

class BasicBlock : public Value {
private:
  static int _counter;
  int _id;
  Function *_function;
  std::vector<std::unique_ptr<Instruction>> _instructions;

public:
  explicit BasicBlock(Function *func);
  [[nodiscard]] Function *getFunction() const { return _function; }

  [[nodiscard]] bool empty() const { return _instructions.empty(); }
  // Check the last instruction
  [[nodiscard]] bool hasTerminator() const;
  void pushInstruction(std::unique_ptr<Instruction> inst);
  [[nodiscard]] Instruction *getTerminator() const;
  [[nodiscard]] Instruction *getInstruction(size_t index) const;
  void insertInstruction(size_t index, std::unique_ptr<Instruction> inst);
  std::unique_ptr<Instruction> eraseInstruction(size_t index);
  [[nodiscard]] size_t size() const { return _instructions.size(); }

  // Get the LLVM like block label
  [[nodiscard]] std::string getLabel() const;
  // Form the .ll IR string for the whole block, including the label and string
  // for all instructions
  [[nodiscard]] std::string str() const override;

  using iterator = std::vector<std::unique_ptr<Instruction>>::iterator;
  using const_iterator =
      std::vector<std::unique_ptr<Instruction>>::const_iterator;

  [[nodiscard]] Instruction *getInstruction(iterator pos) const;
  // Insert using iterator, can be used in other insert functions
  iterator insertInstruction(iterator pos, std::unique_ptr<Instruction> inst);
  // Erase using iterator, move out the ownership
  std::unique_ptr<Instruction> eraseInstruction(iterator pos);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};

} // namespace ir

#endif // IR_BASIC_BLOCK_H
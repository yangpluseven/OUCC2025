#include "ir/instruction.h"

namespace ir {

int Instruction::_counter = 0;

Instruction::Instruction(std::unique_ptr<Type> type, BasicBlock *block)
    : User(std::move(type)), _block(block), _id(_counter++) {}

Instruction::Instruction(std::unique_ptr<Type> type,
                         const std::vector<Value *> &useOperands,
                         BasicBlock *block)
    : User(std::move(type), useOperands), _block(block), _id(_counter++) {}

std::string Instruction::getSSAName() const { return "Unnamed"; }

std::string Instruction::str() const { return "Unknown instruction."; }

void Instruction::remapOperands(const ValueMap &map) {
  for (size_t i = 0; i < operands.size(); ++i) {
    Value *oldVal = operands[i]->getValue();
    auto it = map.find(oldVal);
    if (it != map.end()) {
      operands[i]->setValue(it->second);
    }
  }
  _notRemapped = false;
}
} // namespace ir
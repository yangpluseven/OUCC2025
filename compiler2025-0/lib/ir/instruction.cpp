#include "ir/instruction.h"

namespace ir {

int Instruction::_counter = 0;

Instruction::Instruction(BasicBlock *block, Type *type,
                         const std::vector<Value *> &useOperands)
    : User(type), _block(block), _id(_counter++) {
  for (Value *val : useOperands) {
    operands.push_back(std::make_unique<Use>(this, val));
  }
}

std::string Instruction::getSSAName() const { return "Unnamed"; }

std::string Instruction::getName() const { return "Unknown instruction."; }

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
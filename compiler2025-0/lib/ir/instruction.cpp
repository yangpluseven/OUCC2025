#include "ir/instruction.h"
#include <cassert>
#include <stdexcept>

namespace ir {

int Instruction::_counter = 0;

Instruction::Instruction(std::unique_ptr<Type> type, BasicBlock *block)
    : User(std::move(type)), _block(block), _id(_counter++) {}

Instruction::Instruction(std::unique_ptr<Type> type,
                         const std::vector<Value *> &useOperands,
                         BasicBlock *block)
    : User(std::move(type), useOperands), _block(block), _id(_counter++) {}

std::string Instruction::getSSAName() const {
  return "%v" + std::to_string(getID());
}

std::string Instruction::str() const { return "Unknown instruction."; }

void Instruction::remapValues(const ValueMap &map) {
  auto it = map.find(_cloneTarget->getBlock());
  if (it != map.end()) {
    // Dangerous operation, no type check (ATTENTION)
    auto blockValue = static_cast<BasicBlock *>(it->second);
    setBlock(blockValue);
  }

  for (size_t i = 0; i < _cloneTarget->getNumOperands(); i++) {
    Value *oldVal = _cloneTarget->getOperand(i);
    auto it = map.find(oldVal);
    if (it != map.end()) {
      setOperand(i, it->second);
    } else {
      throw std::runtime_error("Unmapped operands in remapValues.");
    }
  }

  _notRemapped = false;
}
} // namespace ir
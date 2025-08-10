#include "instruction.h"
#include "core.h"
#include <stdexcept>

namespace ir {

int Instruction::_counter = 0;

InstBase::InstBase(std::unique_ptr<Type> type, int id)
    : User(std::move(type)), _id(id) {}

InstBase::InstBase(std::unique_ptr<Type> type,
                   const std::vector<Value *> &useOperands, int id)
    : User(std::move(type), useOperands), _id(id) {}

Instruction::Instruction(std::unique_ptr<Type> type)
    : InstBase(std::move(type), _counter++) {}

Instruction::Instruction(std::unique_ptr<Type> type,
                         const std::vector<Value *> &useOperands)
    : InstBase(std::move(type), useOperands, _counter++) {}

std::string Instruction::getName() const {
  return fmt::format("%v{}", getID());
}

void InstBase::remapValues(const ValueMap &map) {
  auto it = map.find(cloneTarget->getBlock());
  if (it != map.end()) {
    // Dangerous operation, no type check (ATTENTION)
    auto blockValue = static_cast<BasicBlock *>(it->second);
    setBlock(blockValue);
  }

  for (size_t i = 0; i < cloneTarget->getNumOperands(); i++) {
    Value *oldVal = cloneTarget->getOperand(i);
    auto it = map.find(oldVal);
    if (it != map.end()) {
      setOperand(i, it->second);
    } else {
      throw std::runtime_error("Unmapped operands in remapValues.");
    }
  }

  notRemapped = false;
}
} // namespace ir

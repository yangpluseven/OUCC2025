#include "ir/user.h"
#include <cassert>

namespace ir {

User::User(Type *type) : Value(type) {}

void User::addOperand(Value *v) {
  _operands.push_back(std::make_unique<Use>(this, v));
}

void User::setOperand(size_t index, Value *v) {
  assert(index < _operands.size());
  _operands[index]->setValue(v);
}

std::unique_ptr<Use> User::eraseOperand(size_t index) {
  assert(index < _operands.size());
  auto it = _operands.begin() + index;
  auto erased = std::move(*it);
  _operands.erase(it);
  return erased;
}

Value *User::getOperand(size_t index) const {
  assert(index < _operands.size());
  return _operands[index]->getValue();
}

void User::replaceOperand(Value *oldVal, Value *newVal) {
  for (auto &usePtr : _operands) {
    auto use = usePtr.get();
    if (use->getValue() == oldVal) {
      use->setValue(newVal);
    }
  }
}

void User::replaceAllOperands(
    const std::unordered_map<Value *, Value *> &replaceMap) {
  for (auto &usePtr : _operands) {
    auto use = usePtr.get();
    auto it = replaceMap.find(use->getValue());
    if (it != replaceMap.end()) {
      use->setValue(it->second);
    }
  }
}

} // namespace ir

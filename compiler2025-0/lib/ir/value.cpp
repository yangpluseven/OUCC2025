#include "ir/value.h"
#include <cassert>
#include <memory>

namespace ir {

Value::Value(std::unique_ptr<Type> type) : _type(std::move(type)) {
  assert(type);
}

Value::~Value() {
  for (auto *use : _uses) {
    use->setValue(nullptr);
  }
}

void Value::addUse(Use *use) { _uses.insert(use); }

void Value::removeUse(Use *use) { _uses.erase(use); }

void Value::replaceAllUsesWith(Value *newValue) {
  assert(newValue && "Cannot replace with null");
  std::vector<Use *> toReplace(_uses.begin(), _uses.end());
  for (auto *use : toReplace) {
    use->setValue(newValue);
  }
}

} // namespace ir

#include "ir/value.h"
#include <cassert>
#include <memory>

namespace ir {

Value::Value(std::unique_ptr<Type> type) : _type(std::move(type)) {
  assert(_type);
}

Value::~Value() {
  // for (auto *use : _uses) {
  //   use->setValue(nullptr);
  // }
}

std::unique_ptr<BasicType> Value::makeRegType() const {
  if (_type->isBasic() &&
      static_cast<BasicType *>(_type.get())->getBasicKind() == BasicKind::F32) {
    return std::make_unique<BasicType>(BasicKind::F32);
  }
  return std::make_unique<BasicType>(BasicKind::I32);
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

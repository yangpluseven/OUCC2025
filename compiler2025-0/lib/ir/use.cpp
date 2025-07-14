#include "ir/use.h"
#include "ir/value.h"

namespace ir {

Use::Use(User *user, Value *value) : _user(user), _value(value) {
  assert(user && value);
  value->addUse(this);
}

Use::~Use() {
  if (_value) {
    _value->removeUse(this);
  }
}

void Use::setValue(Value *newValue) {
  if (_value)
    _value->removeUse(this);
  _value = newValue;
  if (_value)
    _value->addUse(this);
}

} // namespace ir

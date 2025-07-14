#ifndef IR_VALUE_H
#define IR_VALUE_H

#include "ir/type.h"
#include "ir/use.h"
#include <string>
#include <unordered_set>

namespace ir {

class Value {
protected:
  Type *_type;
  std::unordered_set<Use *> _uses;

public:
  explicit Value(Type *type);
  virtual ~Value();

  [[nodiscard]] Type *getType() const { return _type; }
  [[nodiscard]] size_t getSize() const { return _type->getSize(); }

  void addUse(Use *use);
  void removeUse(Use *use);
  void replaceAllUsesWith(Value *newValue);

  [[nodiscard]] const std::unordered_set<Use *> &getUses() const {
    return _uses;
  }

  virtual std::string getName() const { return ""; }
};

} // namespace ir

#endif // IR_VALUE_H

#ifndef IR_VALUE_H
#define IR_VALUE_H

#include "ir/type.h"
#include "ir/use.h"
#include <string>
#include <unordered_set>
#include <memory>

namespace ir {

class Value {
private:
  std::unique_ptr<Type> _type;
  std::unordered_set<Use *> _uses;

public:
  explicit Value(std::unique_ptr<Type> type);
  virtual ~Value();

  // Return a viewport instead of the actual ownership
  [[nodiscard]] Type *getType() const { return _type.get(); }
  [[nodiscard]] size_t getSize() const { return _type->getSize(); }

  void addUse(Use *use);
  void removeUse(Use *use);
  void replaceAllUsesWith(Value *newValue);

  [[nodiscard]] const std::unordered_set<Use *> &getUses() const {
    return _uses;
  }

  [[nodiscard]] virtual std::string str() const { return "Unnamed"; }
};

} // namespace ir

#endif // IR_VALUE_H

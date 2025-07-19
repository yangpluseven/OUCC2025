#ifndef IR_VALUE_H
#define IR_VALUE_H

#include "ir/type.h"
#include "ir/use.h"
#include <memory>
#include <string>
#include <unordered_set>

namespace ir {

enum class ValueKind { Const, Inst, Global, Block, Function, Arg };

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
  [[nodiscard]] virtual ValueKind getValueKind() const = 0;
  [[nodiscard]] bool isConst() const {
    return getValueKind() == ValueKind::Const;
  }
  [[nodiscard]] bool isGlobal() const {
    return getValueKind() == ValueKind::Global;
  }

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

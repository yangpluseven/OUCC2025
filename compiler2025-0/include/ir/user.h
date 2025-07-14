#ifndef IR_USER_H
#define IR_USER_H

#include "ir/type.h"
#include "ir/value.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace ir {

class User : public Value {
protected:
  std::vector<std::unique_ptr<Use>> _operands;

public:
  explicit User(Type *type);
  ~User() override = default;

  void addOperand(Value *v);
  void setOperand(size_t index, Value *v);
  Value *getOperand(size_t index) const;

  size_t numOperands() const { return _operands.size(); }
  bool empty() const { return _operands.empty(); }
  // Probably no use
  std::unique_ptr<Use> eraseOperand(size_t index);

  void replaceOperand(Value *oldVal, Value *newVal);
  void
  replaceAllOperands(const std::unordered_map<Value *, Value *> &replaceMap);

  using iterator = std::vector<std::unique_ptr<Use>>::iterator;
  using const_iterator = std::vector<std::unique_ptr<Use>>::const_iterator;

  iterator begin() { return _operands.begin(); }
  iterator end() { return _operands.end(); }
  const_iterator begin() const { return _operands.begin(); }
  const_iterator end() const { return _operands.end(); }
};

} // namespace ir

#endif // IR_USER_H

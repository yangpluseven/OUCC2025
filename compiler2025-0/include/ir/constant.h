#ifndef IR_CONSTANT_H
#define IR_CONSTANT_H

#include "ir/number.h"
#include "ir/user.h"
#include <stdexcept>
#include <vector>

namespace ir {

class Constant : public User {
public:
  explicit Constant(Type *type) : User(type) {}

  ~Constant() override;

  virtual std::string str() const override = 0;
};

class ConstantNumber : public Constant {
private:
  Number _value;

  static BasicType *determineType(const Number &num);
  BasicKind getBasicKind() const;

public:
  explicit ConstantNumber(bool value);
  explicit ConstantNumber(const Number &num);
  ConstantNumber(const ConstantNumber &other);
  ConstantNumber(ConstantNumber &&other) noexcept;

  Number getValue() const;
  float floatValue() const;
  int intValue() const;

  ConstantNumber operator+(const ConstantNumber &rhs) const;
  ConstantNumber operator-(const ConstantNumber &rhs) const;
  ConstantNumber operator*(const ConstantNumber &rhs) const;
  ConstantNumber operator/(const ConstantNumber &rhs) const;
  ConstantNumber operator%(const ConstantNumber &rhs) const;
  ConstantNumber operator^(const ConstantNumber &rhs) const;
  ConstantNumber operator-() const;
  ConstantNumber operator!() const;
  ConstantNumber operator==(const ConstantNumber &rhs) const;
  ConstantNumber operator!=(const ConstantNumber &rhs) const;
  ConstantNumber operator>(const ConstantNumber &rhs) const;
  ConstantNumber operator>=(const ConstantNumber &rhs) const;
  ConstantNumber operator<(const ConstantNumber &rhs) const;
  ConstantNumber operator<=(const ConstantNumber &rhs) const;

  std::string getLiteralStr() const;
  std::string str() const override;
};

class ConstantZero : public Constant {
public:
  explicit ConstantZero(Type *type);

  std::string str() const override;
};

class ConstantArray : public Constant {
private:
  std::vector<std::unique_ptr<Constant>> values;

public:
  ConstantArray(Type *type, std::vector<std::unique_ptr<Constant>> values);

  const Constant *getValue(size_t index) const;

  std::string str() const override;
};

} // namespace ir

#endif // IR_CONSTANT_H
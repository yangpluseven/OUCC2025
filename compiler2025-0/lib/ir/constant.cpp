#include "ir/constant.h"
#include "ir/type.h"
#include "ir/value.h"

#include <sstream>
#include <utility>

namespace ir {

Constant::Constant(Type *type) : ir::User(type) {}

Constant::~Constant() = default;

BasicType *ConstantNumber::determineType(const Number &num) {
  auto value = num.getValue();
  if (std::holds_alternative<int>(value))
    return BasicType::get(BasicKind::I32);
  else if (std::holds_alternative<float>(value))
    return BasicType::get(BasicKind::F32);
  else
    throw std::runtime_error("Unsupported value");
}

ConstantNumber::ConstantNumber(bool value)
    : Constant(BasicType::get(BasicKind::I1)), _value(value ? 1 : 0) {}

ConstantNumber::ConstantNumber(const Number &num)
    : Constant(determineType(num)), _value(num) {}

ConstantNumber::ConstantNumber(const ConstantNumber &other)
    : Constant(other.getType()), _value(other._value) {}

ConstantNumber::ConstantNumber(ConstantNumber &&other) noexcept
    : Constant(other.getType()), _value(std::move(other._value)) {}

Number ConstantNumber::getValue() const { return _value; }

float ConstantNumber::floatValue() const { return _value.floatValue(); }

int ConstantNumber::intValue() const { return _value.intValue(); }

std::string ConstantNumber::getLiteralStr() const {
  if (getType() == BasicType::get(BasicKind::I1))
    return intValue() ? "true" : "false";
  else if (getType() == BasicType::get(BasicKind::I32))
    return std::to_string(intValue());
  else if (getType() == BasicType::get(BasicKind::F32)) {
    auto value = floatValue();
    std::stringstream ss;
    ss << "0x" << std::hex << std::uppercase
       << *reinterpret_cast<unsigned int *>(&value);
    return ss.str();
  } else
    throw std::runtime_error("Unexpected type");
}

ConstantNumber ConstantNumber::operator+(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(Number(intValue() + rhs.intValue()));
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(Number(floatValue() + rhs.floatValue()));
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator-(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(Number(intValue() - rhs.intValue()));
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(Number(floatValue() - rhs.floatValue()));
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator*(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(Number(intValue() * rhs.intValue()));
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(Number(floatValue() * rhs.floatValue()));
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator/(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(Number(intValue() / rhs.intValue()));
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(Number(floatValue() / rhs.floatValue()));
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator%(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(Number(intValue() % rhs.intValue()));
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator^(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32))
    return ConstantNumber(Number(intValue() ^ rhs.intValue()));
  else if (getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber((intValue() ^ rhs.intValue()) != 0);
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator-() const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(Number(-intValue()));
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(Number(-floatValue()));
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator!() const {
  if (getType() == BasicType::get(BasicKind::I1) ||
      getType() == BasicType::get(BasicKind::I32))
    return ConstantNumber(intValue() == 0);
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(floatValue() == 0.0f);
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator==(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(intValue() == rhs.intValue());
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(floatValue() == rhs.floatValue());
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator!=(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(intValue() != rhs.intValue());
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(floatValue() != rhs.floatValue());
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator>(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(intValue() > rhs.intValue());
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(floatValue() > rhs.floatValue());
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator>=(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(intValue() >= rhs.intValue());
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(floatValue() >= rhs.floatValue());
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator<(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(intValue() < rhs.intValue());
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(floatValue() < rhs.floatValue());
  else
    throw std::runtime_error("Unsupported type");
}

ConstantNumber ConstantNumber::operator<=(const ConstantNumber &rhs) const {
  if (getType() == BasicType::get(BasicKind::I32) ||
      getType() == BasicType::get(BasicKind::I1))
    return ConstantNumber(intValue() <= rhs.intValue());
  else if (getType() == BasicType::get(BasicKind::F32))
    return ConstantNumber(floatValue() <= rhs.floatValue());
  else
    throw std::runtime_error("Unsupported type");
}

std::string ConstantNumber::str() const {
  return getType()->str() + " " + getLiteralStr();
}

ConstantZero::ConstantZero(Type *type) : Constant(type) {}

std::string ConstantZero::str() const {
  return getType()->str() + " zeroinitializer";
}

ConstantArray::ConstantArray(Type *type, std::vector<Constant *> values)
    : Constant(getType()), values(std::move(values)) {}

std::vector<Constant *> &ConstantArray::getValues() { return values; }

std::string ConstantArray::str() const {
  std::ostringstream oss;
  oss << getType()->str() << " [";
  for (size_t i = 0; i < values.size(); ++i) {
    oss << values[i]->str();
    if (i + 1 < values.size())
      oss << ", ";
  }
  oss << "]";
  return oss.str();
}

} // namespace ir
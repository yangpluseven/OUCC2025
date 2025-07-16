#include "ir/constant.h"
#include "ir/type.h"
#include "ir/value.h"

#include <cassert>
#include <sstream>
#include <utility>

namespace ir {

Constant::~Constant() = default;

BasicType *ConstantNumber::determineType(const Number &num) {
  const auto &value = num.getValue();
  if (std::holds_alternative<int>(value))
    return BasicType::get(BasicKind::I32);
  else if (std::holds_alternative<float>(value))
    return BasicType::get(BasicKind::F32);
  else
    throw std::runtime_error("Unsupported number type");
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
int ConstantNumber::intValue() const { return _value.intValue(); }
float ConstantNumber::floatValue() const { return _value.floatValue(); }

BasicKind ConstantNumber::getBasicKind() const {
  assert(getType()->isBasic());
  return static_cast<BasicType *>(getType())->getBasicKind();
}

std::string ConstantNumber::getLiteralStr() const {
  switch (getBasicKind()) {
  case BasicKind::I1:
    return intValue() ? "true" : "false";
  case BasicKind::I32:
    return std::to_string(intValue());
  case BasicKind::F32: {
    float value = floatValue();
    std::stringstream ss;
    ss << "0x" << std::hex << std::uppercase
       << *reinterpret_cast<unsigned int *>(&value);
    return ss.str();
  }
  default:
    throw std::runtime_error("Unexpected type");
  }
}

std::string ConstantNumber::str() const {
  return getType()->str() + " " + getLiteralStr();
}

// General operators for integer/float
#define DEFINE_BINARY_OP(OPNAME, OP)                                           \
  ConstantNumber ConstantNumber::operator OPNAME(const ConstantNumber &rhs)    \
      const {                                                                  \
    switch (getBasicKind()) {                                                  \
    case BasicKind::I1:                                                        \
    case BasicKind::I32:                                                       \
      return ConstantNumber(Number(intValue() OP rhs.intValue()));             \
    case BasicKind::F32:                                                       \
      return ConstantNumber(Number(floatValue() OP rhs.floatValue()));         \
    default:                                                                   \
      throw std::runtime_error("Unsupported type in " #OPNAME);                \
    }                                                                          \
  }

DEFINE_BINARY_OP(+, +)
DEFINE_BINARY_OP(-, -)
DEFINE_BINARY_OP(*, *)
DEFINE_BINARY_OP(/, /)
DEFINE_BINARY_OP(==, ==)
DEFINE_BINARY_OP(!=, !=)
DEFINE_BINARY_OP(>, >)
DEFINE_BINARY_OP(>=, >=)
DEFINE_BINARY_OP(<, <)
DEFINE_BINARY_OP(<=, <=)

// Operators for only integer
ConstantNumber ConstantNumber::operator%(const ConstantNumber &rhs) const {
  switch (getBasicKind()) {
  case BasicKind::I1:
  case BasicKind::I32:
    return ConstantNumber(Number(intValue() % rhs.intValue()));
  default:
    throw std::runtime_error("Modulo not supported for this type");
  }
}

ConstantNumber ConstantNumber::operator^(const ConstantNumber &rhs) const {
  switch (getBasicKind()) {
  case BasicKind::I1:
    return ConstantNumber((intValue() ^ rhs.intValue()) != 0);
  case BasicKind::I32:
    return ConstantNumber(Number(intValue() ^ rhs.intValue()));
  default:
    throw std::runtime_error("Bitwise XOR not supported for this type");
  }
}

// Unary
ConstantNumber ConstantNumber::operator-() const {
  switch (getBasicKind()) {
  case BasicKind::I1:
  case BasicKind::I32:
    return ConstantNumber(Number(-intValue()));
  case BasicKind::F32:
    return ConstantNumber(Number(-floatValue()));
  default:
    throw std::runtime_error("Unary minus not supported for this type");
  }
}

ConstantNumber ConstantNumber::operator!() const {
  switch (getBasicKind()) {
  case BasicKind::I1:
  case BasicKind::I32:
    return ConstantNumber(intValue() == 0);
  case BasicKind::F32:
    return ConstantNumber(floatValue() == 0.0f);
  default:
    throw std::runtime_error("Logical not not supported for this type");
  }
}

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

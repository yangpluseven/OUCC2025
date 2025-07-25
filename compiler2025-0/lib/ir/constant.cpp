#include "ir/constant.h"
#include "ir/type.h"
#include "ir/value.h"

#include <cassert>
#include <sstream>
#include <utility>

namespace ir {

Constant::~Constant() = default;

std::unique_ptr<BasicType> ConstantNumber::determineType(const Number &num) {
  const auto &value = num.getValue();
  if (std::holds_alternative<int>(value))
    return std::make_unique<BasicType>(BasicKind::I32);
  else if (std::holds_alternative<float>(value))
    return std::make_unique<BasicType>(BasicKind::F32);
  else
    throw std::runtime_error("Unsupported number type");
}

ConstantNumber::ConstantNumber(bool value)
    : Constant(std::make_unique<BasicType>(BasicKind::I1)),
      _value(value ? 1 : 0) {}

ConstantNumber::ConstantNumber(const Number &num)
    : Constant(determineType(num)), _value(num) {}

// Probably should just move the type (ATTENTION)
ConstantNumber::ConstantNumber(ConstantNumber &&other) noexcept
    : Constant(std::move(other.getType()->clone())),
      _value(std::move(other._value)) {}

Number ConstantNumber::getValue() const { return _value; }
int ConstantNumber::intValue() const { return _value.intValue(); }
float ConstantNumber::floatValue() const { return _value.floatValue(); }

// BasicKind ConstantNumber::getBasicKind() const {
//   assert(getType()->isBasic());
//   return static_cast<BasicType *>(getType())->getBasicKind();
// }

std::string ConstantNumber::getLiteralStr() const {
  auto basicKind = static_cast<BasicType *>(getType())->getBasicKind();
  switch (basicKind) {
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

std::string ConstantNumber::getName() const { return getLiteralStr(); }

// General operators for integer/float

#define DEFINE_BINARY_OP(OPNAME, OP)                                           \
  ConstantNumber ConstantNumber::operator OPNAME(const ConstantNumber &rhs)    \
      const {                                                                  \
    auto basicKind = static_cast<BasicType *>(getType())->getBasicKind();      \
    switch (basicKind) {                                                       \
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
  auto basicKind = static_cast<BasicType *>(getType())->getBasicKind();
  switch (basicKind) {
  case BasicKind::I1:
  case BasicKind::I32:
    return ConstantNumber(Number(intValue() % rhs.intValue()));
  default:
    throw std::runtime_error("Modulo not supported for this type");
  }
}

ConstantNumber ConstantNumber::operator^(const ConstantNumber &rhs) const {
  auto basicKind = static_cast<BasicType *>(getType())->getBasicKind();
  switch (basicKind) {
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
  auto basicKind = static_cast<BasicType *>(getType())->getBasicKind();
  switch (basicKind) {
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
  auto basicKind = static_cast<BasicType *>(getType())->getBasicKind();
  switch (basicKind) {
  case BasicKind::I1:
  case BasicKind::I32:
    return ConstantNumber(intValue() == 0);
  case BasicKind::F32:
    return ConstantNumber(floatValue() == 0.0f);
  default:
    throw std::runtime_error("Logical not not supported for this type");
  }
}

std::string ConstantZero::getName() const { return "zeroinitializer"; }

std::string ConstantZero::str() const {
  return getType()->str() + " " + getName();
}

Constant *ConstantArray::getValue(size_t index) const {
  assert(index < _values.size());
  return _values[index].get();
}

std::string ConstantArray::getName() const {
  std::ostringstream oss;
  oss << "[";
  for (size_t i = 0; i < _values.size(); ++i) {
    oss << _values[i]->str();
    if (i + 1 < _values.size())
      oss << ", ";
  }
  oss << "]";
  return oss.str();
}

std::string ConstantArray::str() const {
  return getType()->str() + " " + getName();
}

} // namespace ir

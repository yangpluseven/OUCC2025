#include "reg/register.h"

int VReg::_counter = 0;

RegKind VReg::getRegKind() const { return RegKind::Virtual; }

std::string VReg::str() const {
  switch (regType) {
  case RegType::INT:
    return "$i" + std::to_string(_id);
  case RegType::FLOAT:
    return "$f" + std::to_string(_id);
  default:
    throw std::runtime_error("Unknown register type.");
  }
}
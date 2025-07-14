#include "ir/type.h"
#include <cassert>
#include <sstream>

namespace ir {

//
// ======== UTILITY: Type::isEqual ========
//

bool Type::isEqual(const Type *lhs, const Type *rhs) {
  if (lhs == rhs)
    return true;
  if (!lhs || !rhs)
    return false;

  if (lhs->getKind() != rhs->getKind())
    return false;

  switch (lhs->getKind()) {
  case TypeKind::BASIC: {
    auto lhsBasic = static_cast<const BasicType *>(lhs);
    auto rhsBasic = static_cast<const BasicType *>(rhs);
    return lhsBasic->getBasicKind() == rhsBasic->getBasicKind();
  }
  case TypeKind::ARRAY: {
    auto lhsArr = static_cast<const ArrayType *>(lhs);
    auto rhsArr = static_cast<const ArrayType *>(rhs);
    return lhsArr->getLength() == rhsArr->getLength() &&
           isEqual(lhsArr->getElementType(), rhsArr->getElementType());
  }
  case TypeKind::POINTER: {
    auto lhsPtr = static_cast<const PointerType *>(lhs);
    auto rhsPtr = static_cast<const PointerType *>(rhs);
    return isEqual(lhsPtr->getPointeeType(), rhsPtr->getPointeeType());
  }
  }

  return false; // unreachable
}

//
// ======== BASIC TYPE ========
//

static BasicType i1Type(BasicKind::I1);
static BasicType i32Type(BasicKind::I32);
static BasicType f32Type(BasicKind::F32);

BasicType *BasicType::get(BasicKind kind) {
  switch (kind) {
  case BasicKind::I1:
    return &i1Type;
  case BasicKind::I32:
    return &i32Type;
  case BasicKind::F32:
    return &f32Type;
  default:
    return nullptr;
  }
}

BasicType::BasicType(BasicKind kind) : _kind(kind) {}

size_t BasicType::getSize() const {
  switch (_kind) {
  case BasicKind::I1:
    return 1;
  case BasicKind::I32:
    return 4;
  case BasicKind::F32:
    return 4;
  default:
    return 0;
  }
}

std::string BasicType::str() const {
  switch (_kind) {
  case BasicKind::I1:
    return "i1";
  case BasicKind::I32:
    return "i32";
  case BasicKind::F32:
    return "f32";
  default:
    return "unknown";
  }
}

//
// ======== ARRAY TYPE ========
//

ArrayType::ArrayType(Type *elementType, size_t arraySize)
    : _elementType(elementType), _arraySize(arraySize) {
  assert(elementType && "Element type cannot be null");
}

size_t ArrayType::getSize() const {
  return _arraySize * _elementType->getSize();
}

std::string ArrayType::str() const {
  std::ostringstream oss;
  oss << "[" << _arraySize << " x " << _elementType->str() << "]";
  return oss.str();
}

std::vector<size_t> ArrayType::getDimensions() const {
  std::vector<size_t> dims;
  const Type *curr = this;

  while (curr->isArray()) {
    auto arr = static_cast<const ArrayType *>(curr);
    dims.push_back(arr->getLength());
    curr = arr->getElementType();
  }

  return dims;
}

Type *ArrayType::getInnermostElementType() const {
  const Type *curr = this;
  while (curr->isArray()) {
    curr = static_cast<const ArrayType *>(curr)->getElementType();
  }
  return const_cast<Type *>(curr);
}

//
// ======== POINTER TYPE ========
//

PointerType::PointerType(Type *pointeeType) : _pointeeType(pointeeType) {
  assert(pointeeType && "Pointee type cannot be null");
}

size_t PointerType::getSize() const {
  return 8; // Assume 64-bit pointer
}

std::string PointerType::str() const { return _pointeeType->str() + "*"; }

} // namespace ir

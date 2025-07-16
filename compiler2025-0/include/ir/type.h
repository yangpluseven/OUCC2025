#ifndef IR_TYPE_H
#define IR_TYPE_H

#include <cassert>
#include <memory>
#include <string>
#include <vector>

namespace ir {

enum class TypeKind { BASIC, ARRAY, POINTER };

class Type {
public:
  virtual ~Type() = default;

  [[nodiscard]] virtual TypeKind getTypeKind() const = 0;
  // Is recommended to use type check + static cast + unique function for
  // ArrayType and PointerType
  [[nodiscard]] virtual Type *getBaseType() const = 0;
  [[nodiscard]] virtual size_t getSize() const = 0;
  // Get the LLVM like string, example: i32
  [[nodiscard]] virtual std::string str() const = 0;
  [[nodiscard]] virtual std::unique_ptr<Type> clone() const = 0;

  bool isBasic() const { return getTypeKind() == TypeKind::BASIC; }
  bool isArray() const { return getTypeKind() == TypeKind::ARRAY; }
  bool isPointer() const { return getTypeKind() == TypeKind::POINTER; }

  static bool isEqual(const Type *lhs, const Type *rhs);
  bool operator==(const Type &rhs) const { return isEqual(this, &rhs); }
};

//
// ======== BASIC TYPE ========
//

enum class BasicKind { I1, I32, F32, VOID };

// Any comparison or identification needs to be done with enum class BasicKind,
// check function isEqual in class Type
class BasicType : public Type {
public:
  explicit BasicType(BasicKind kind);

  [[nodiscard]] TypeKind getTypeKind() const override {
    return TypeKind::BASIC;
  }
  [[nodiscard]] size_t getSize() const override;
  // Should not be called
  [[nodiscard]] Type *getBaseType() const override { return nullptr; }
  [[nodiscard]] BasicKind getBasicKind() const { return _kind; }

  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Type> clone() const override;

private:
  BasicKind _kind;
};

//
// ======== ARRAY TYPE ========
//

class ArrayType : public Type {
public:
  explicit ArrayType(std::unique_ptr<Type> elementType, size_t arraySize);

  [[nodiscard]] TypeKind getTypeKind() const override {
    return TypeKind::ARRAY;
  }
  [[nodiscard]] size_t getSize() const override;
  // Recommend getElementType()
  [[nodiscard]] Type *getBaseType() const override {
    return _elementType.get();
  }
  // Return a viewport instead of the actual ownership
  [[nodiscard]] Type *getElementType() const { return _elementType.get(); }
  [[nodiscard]] size_t getLength() const { return _arrayLength; }

  // Get all dimensions like: int[2][3][4] => [2, 3, 4]
  [[nodiscard]] std::vector<size_t> getDimensions() const;

  // The innermost scaler type int/float of this (one or multi-dims) array
  [[nodiscard]] BasicType *getInnermostElementType() const;

  [[nodiscard]] std::unique_ptr<Type> clone() const override;
  [[nodiscard]] std::string str() const override;

private:
  std::unique_ptr<Type> _elementType;
  size_t _arrayLength;
};

//
// ======== POINTER TYPE ========
//

class PointerType : public Type {
public:
  explicit PointerType(std::unique_ptr<Type> pointeeType);

  [[nodiscard]] TypeKind getTypeKind() const override {
    return TypeKind::POINTER;
  }
  [[nodiscard]] size_t getSize() const override;
  // Recommend getPointeeType()
  [[nodiscard]] Type *getBaseType() const override {
    return _pointeeType.get();
  }
  // Return a viewport instead of the actual ownership
  [[nodiscard]] Type *getPointeeType() const { return _pointeeType.get(); }

  [[nodiscard]] std::string str() const override;
  [[nodiscard]] std::unique_ptr<Type> clone() const override;

private:
  std::unique_ptr<Type> _pointeeType;
};

} // namespace ir

#endif // IR_TYPE_H

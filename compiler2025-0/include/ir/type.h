#ifndef IR_TYPE_H
#define IR_TYPE_H

#include <cassert>
#include <string>
#include <vector>

namespace ir {

enum class TypeKind { BASIC, ARRAY, POINTER };

class Type {
public:
  virtual ~Type() = default;

  [[nodiscard]] virtual TypeKind getKind() const = 0;
  [[nodiscard]] virtual Type *baseType() const = 0;
  [[nodiscard]] virtual size_t getSize() const = 0;
  [[nodiscard]] virtual std::string str() const = 0;

  // 类型判断工具方法
  bool isBasic() const { return getKind() == TypeKind::BASIC; }
  bool isArray() const { return getKind() == TypeKind::ARRAY; }
  bool isPointer() const { return getKind() == TypeKind::POINTER; }

  // 类型等价检查
  static bool isEqual(const Type *lhs, const Type *rhs);
  bool operator==(const Type &rhs) const { return isEqual(this, &rhs); }
};

//
// ======== BASIC TYPE ========
//

enum class BasicKind { I1, I32, F32 };

class BasicType : public Type {
public:
  // Do not call this, use get() instead
  explicit BasicType(BasicKind kind);
  static BasicType *get(BasicKind kind);

  [[nodiscard]] TypeKind getKind() const override { return TypeKind::BASIC; }
  [[nodiscard]] BasicKind getBasicKind() const { return _kind; }
  [[nodiscard]] size_t getSize() const override;
  [[nodiscard]] std::string str() const override;
  [[nodiscard]] Type *baseType() const override { return nullptr; }

private:
  BasicKind _kind;
};

//
// ======== ARRAY TYPE ========
//

class ArrayType : public Type {
public:
  ArrayType(Type *elementType, size_t arraySize);

  [[nodiscard]] TypeKind getKind() const override { return TypeKind::ARRAY; }
  [[nodiscard]] size_t getSize() const override;
  [[nodiscard]] std::string str() const override;

  [[nodiscard]] Type *baseType() const override { return _elementType; }
  [[nodiscard]] Type *getElementType() const { return _elementType; }
  [[nodiscard]] size_t getLength() const { return _arraySize; }

  // 获取所有维度，如 int[2][3][4] => [2, 3, 4]
  [[nodiscard]] std::vector<size_t> getDimensions() const;

  // 最内层的标量类型（int/float）
  [[nodiscard]] Type *getInnermostElementType() const;

private:
  Type *_elementType;
  size_t _arraySize;
};

//
// ======== POINTER TYPE ========
//

class PointerType : public Type {
public:
  explicit PointerType(Type *pointeeType);

  [[nodiscard]] TypeKind getKind() const override { return TypeKind::POINTER; }
  [[nodiscard]] size_t getSize() const override;
  [[nodiscard]] std::string str() const override;

  [[nodiscard]] Type *baseType() const override { return _pointeeType; }
  [[nodiscard]] Type *getPointeeType() const { return _pointeeType; }

private:
  Type *_pointeeType;
};

} // namespace ir

#endif // IR_TYPE_H

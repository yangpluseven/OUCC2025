#ifndef REG_REGISTER_H
#define REG_REGISTER_H

#include <stdexcept>
#include <vector>

enum class RegKind { Virtual, Machine };
enum class RegType { INT, FLOAT };

class Reg {
protected:
  RegType regType;

  explicit Reg(RegType type) : regType(type) {}

public:
  virtual ~Reg() = default;
  virtual RegKind getRegKind() const = 0;
  virtual std::string str() const = 0;
};

class VReg : public Reg {
private:
  static int _counter;
  int _id;

public:
  explicit VReg(RegType type) : Reg(type), _id(_counter++) {}
  RegKind getRegKind() const override;
  std::string str() const override;
};

#endif // REG_REGISTER_H
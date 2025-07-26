#ifndef RISCV_MACHINE_BLOCK_H
#define RISCV_MACHINE_BLOCK_H

#include "ir/basic_block.h"
#include "ir/type.h"

namespace riscv {

class MachineFunc;

class MachineBlock : public ir::BlockBase {
private:
  static int _counter;

public:
  MachineBlock();
  explicit  MachineBlock(int id);

  ir::ValueKind getValueKind() const override {
    return ir::ValueKind::MachineBlock;
  }

  std::string getLabel() const override;
  std::string getName() const override;
};

class MachineFunc : public ir::FuncBase {
private:
  ir::Function *_origin;
  const int _localSize, _iCallerNum, _fCallerNum;

public:
  int maxFuncParamNum = 0;

  // Not sure about the type but I guess it's fine (ATTENTION)
  MachineFunc(ir::Function *func, int localSize, int iCallerNum,
              int fCallerNum);

  [[nodiscard]] int getFCallerNum() const { return _fCallerNum; }
  [[nodiscard]] int getICallerNum() const { return _iCallerNum; }
  [[nodiscard]] int getLocalSize() const { return _localSize; }
  [[nodiscard]] std::string getName() const { return getRawName(); }
};

} // namespace riscv

#endif
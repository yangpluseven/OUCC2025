#ifndef RISCV_MACHINE_BLOCK_H
#define RISCV_MACHINE_BLOCK_H

#include "ir/basic_block.h"
#include "ir/instructions.h"
#include "ir/type.h"

namespace riscv {

class MachineFunc;

class MachineBlock : public ir::BlockBase {
private:
  static int _counter;

public:
  MachineBlock();
  explicit MachineBlock(int id);

  ir::ValueKind getValueKind() const override {
    return ir::ValueKind::MachineBlock;
  }

  std::string getLabel() const override;
  std::string getName() const override;
};

class MachineFunc : public ir::FuncBase {
private:
  ir::Function *_origin;
  int _localSize, _iCallerNum, _fCallerNum;
  std::unordered_map<ir::AllocaInst *, int> _localOffsets;
  std::unordered_map<ir::Argument *, std::pair<bool, int>> _argOffsets;

  void initCallerNums();
  void initLocalOffsets();
  void initArgOffsets();

public:
  int maxFuncParamNum = 0;

  // Not sure about the type but I guess it's fine (ATTENTION)
  MachineFunc(ir::Function *func);

  [[nodiscard]] int getFCallerNum() const { return _fCallerNum; }
  [[nodiscard]] int getICallerNum() const { return _iCallerNum; }
  [[nodiscard]] int getLocalSize() const { return _localSize; }
  [[nodiscard]] std::string getName() const { return getRawName(); }
};

} // namespace riscv

#endif
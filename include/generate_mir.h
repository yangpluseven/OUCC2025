#ifndef RISCV_GENERATE_MIR_H
#define RISCV_GENERATE_MIR_H

#include "machine_func.h"
#include "module.h"
#include "registers.h"
#include "type.h"

namespace riscv {

class GenerateMIR {
private:
  ir::Module *_module;
  bool _isProcessed = false;
  bool _opti = false;

  void makeMachineBlocks(MachineFunc *mFunc);
  std::unique_ptr<MachineFunc> funcToMIR(ir::Function *func);

  void moduleToMIR() {
    for (auto func : _module->getFunctions()) {
      if (!func->empty()) {
        _module->addMFunction(funcToMIR(func));
      }
    }
  }

public:
  explicit GenerateMIR(ir::Module *module, bool opti)
      : _module(module), _opti(opti) {}

  void generate() {
    if (_isProcessed) {
      return;
    }
    moduleToMIR();
    _isProcessed = true;
  }
};

} // namespace riscv

#endif

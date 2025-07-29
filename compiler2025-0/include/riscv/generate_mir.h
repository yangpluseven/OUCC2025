#ifndef RISCV_GENERATE_MIR_H
#define RISCV_GENERATE_MIR_H

#include "ir/module.h"
#include "ir/type.h"
#include "riscv/machine_func.h"
#include "riscv/registers.h"

namespace riscv
{

class GenerateMIR
{
private:
    ir::Module *_module;
    bool _isProcessed = false;

    std::unique_ptr<MachineFunc> funcToMIR(ir::Function *func);

    void moduleToMIR()
    {
        for (auto func : _module->getFunctions())
        {
            if (!func->empty())
            {
                _module->addMFunction(funcToMIR(func));
            }
        }
    }

public:
    explicit GenerateMIR(ir::Module *module) : _module(module)
    {
    }

    void generate()
    {
        if (_isProcessed)
        {
            return;
        }
        moduleToMIR();
        _isProcessed = true;
    }
};

} // namespace riscv

#endif

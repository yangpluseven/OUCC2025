#ifndef PASS_PASS_MANAGER_H
#define PASS_PASS_MANAGER_H

#include "module.h"
#include "passes.h"

namespace pass {
class PassManager {
private:
  const ir::Module *_module;

public:
  explicit PassManager(const ir::Module *module) : _module(module) {}

  void run() const {
    bool changed = true;
    while (changed) {
      changed = false;
      changed |= DeadCodeElim(_module).onModule();
      changed |= ConstProp(_module).onModule();
    }
  }

  void runLower() const { return; }

  void runLast() const { RemoveJump(_module).onModule(); }
};
} // namespace pass

#endif // PASS_PASS_MANAGER_HPP
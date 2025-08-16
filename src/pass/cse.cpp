#include "passes.h"

namespace pass {

bool CommonExpElim::onFunction(ir::Function *function) {
  bool changed = false;
  std::unordered_map<std::string, ir::Instruction *> expMap;
  std::vector<ir::Instruction *> toErase;
  for (auto &blockPtr : *function) {
    auto block = static_cast<ir::BasicBlock *>(blockPtr.get());
    expMap.clear();
    toErase.clear();
    for (auto &instPtr : *block) {
      auto inst = static_cast<ir::Instruction *>(instPtr.get());

      auto instKind = inst->getInstKind();
      switch (instKind) {
        case ir::InstKind::Alloca:
        case ir::InstKind::Call:
        case ir::InstKind::Branch:
        case ir::InstKind::Ret:
        case ir::InstKind::Phi:
        case ir::InstKind::Load:
        case ir::InstKind::Store:
          // Skip these instructions
          continue;
        default:
          break;
      }

      auto str = inst->baseStr();
      if (str.empty()) {
        continue;
      }
      if (expMap.find(str) != expMap.end() && expMap.at(str) != nullptr) {
        inst->replaceAllUsesWith(expMap.at(str));
        toErase.push_back(inst);
        changed = true;
      } else {
        expMap[str] = inst;
      }
    }
    for (auto *inst : toErase) {
      block->eraseInstruction(inst);
    }
  }
  return changed;
}

} // namespace pass
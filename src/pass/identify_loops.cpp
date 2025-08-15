#include "passes.h"

namespace pass {

bool IdentifyLoops::onFunction(ir::Function *function) {
  function->calcIndexInFunc();
  for (auto &blockPtr : *function) {
    auto block = static_cast<ir::BasicBlock *>(blockPtr.get());
    bool isLoopEntry = false;
    for (auto &use : block->getUses()) {
      auto inst = static_cast<ir::Instruction *>(use->getUser());
      if (inst->getInstKind() != ir::InstKind::Branch) {
        continue;
      }
      if (inst->getBlock()->getIndexInFunc() > block->getIndexInFunc()) {
        isLoopEntry = true;
        break; // Found a branch instruction that jumps back to this block, it's
               // a loop
      }
    }
    if (!isLoopEntry) {
      continue; // Not a loop entry block
    }
    auto branchInst = static_cast<ir::BranchInst *>(block->getTerminator());
    auto leaveBB = static_cast<ir::BasicBlock *>(branchInst->getOperand(2));
    auto loopInfo =
        new ir::LoopInfo(block->getIndexInFunc(), leaveBB->getIndexInFunc());

    function->loops.push_back(loopInfo);
  }
  return false;
}

} // namespace pass
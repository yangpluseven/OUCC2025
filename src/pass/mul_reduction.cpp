#include "mir_util.h"
#include "passes.h"

#define MAKE_I32 std::make_unique<ir::BasicType>(ir::BasicKind::I32)

namespace pass {

size_t reduction(riscv::MachineBlock *mBlock, size_t index, int imm,
                 riscv::MachineInst *src) {
  auto mInst = mBlock->getMInst(index);
  auto mulOp = static_cast<riscv::RRR *>(mInst)->getOp();
  riscv::RRROp addOp =
      mulOp == riscv::RRROp::MULW ? riscv::RRROp::ADDW : riscv::RRROp::ADD;
  riscv::RRIOp slOp =
      mulOp == riscv::RRROp::MULW ? riscv::RRIOp::SLLIW : riscv::RRIOp::SLLI;
  riscv::RRROp subOp =
      mulOp == riscv::RRROp::MULW ? riscv::RRROp::SUBW : riscv::RRROp::SUB;
  auto dest = mInst->getDest();
  if (imm == 0) {
    auto inst = std::make_unique<riscv::LI>(dest, 0);
    mInst->replaceAllUsesWith(inst.get());
    mBlock->setInstruction(index, std::move(inst));
    return index;
  }
  if (imm == 1) {
    auto inst = std::make_unique<riscv::RR>(riscv::RROp::MV, dest, src);
    mInst->replaceAllUsesWith(inst.get());
    mBlock->setInstruction(index, std::move(inst));
    return index;
  }
  if (imm == -1) {
    auto inst = std::make_unique<riscv::RR>(riscv::RROp::NEG, dest, src);
    mInst->replaceAllUsesWith(inst.get());
    mBlock->setInstruction(index, std::move(inst));
    return index;
  }
  if (riscv::bitcount(imm) == 1) {
    auto inst = std::make_unique<riscv::RRI>(riscv::RRIOp::SLLIW, dest, src,
                                             riscv::trailingZeros(imm));
    mInst->replaceAllUsesWith(inst.get());
    mBlock->setInstruction(index, std::move(inst));
    return index;
  }
  if (riscv::bitcount(imm) == 2 && imm % 2 == 1) {
    auto midInst = std::make_unique<riscv::RRI>(slOp, MAKE_I32, src,
                                                31 - riscv::leadingZeros(imm));
    auto inst = std::make_unique<riscv::RRR>(addOp, dest, midInst.get(), src);
    mInst->replaceAllUsesWith(inst.get());
    mBlock->setInstruction(index, std::move(inst));
    mBlock->insertInstruction(index, std::move(midInst));
    return index + 1;
  }
  if (riscv::trailingZeros(imm) == 0 &&
      riscv::leadingZeros(imm) + riscv::bitcount(imm) == 32) {
    auto midInst = std::make_unique<riscv::RRI>(slOp, MAKE_I32, src,
                                                32 - riscv::leadingZeros(imm));
    auto inst = std::make_unique<riscv::RRR>(subOp, dest, midInst.get(), src);
    mInst->replaceAllUsesWith(inst.get());
    mBlock->setInstruction(index, std::move(inst));
    mBlock->insertInstruction(index, std::move(midInst));
    return index + 1;
  }
  return index;
}

bool MultiplyReduction::onFunction(riscv::MachineFunc *function) {
  bool modified = false;
  for (auto &blockPtr : *function) {
    auto mBlock = static_cast<riscv::MachineBlock *>(blockPtr.get());
    for (size_t i = 0; i < mBlock->size(); i++) {
      auto mInst = mBlock->getMInst(i);
      if (mInst->getMInstKind() != riscv::MInstKind::RRR) {
        continue;
      }
      auto rrrInst = static_cast<riscv::RRR *>(mInst);
      if (rrrInst->getOp() != riscv::RRROp::MULW &&
          rrrInst->getOp() != riscv::RRROp::MUL) {
        continue;
      }
      if (rrrInst->getType()->isF32()) {
        continue; // Skip float multiplication
      }
      auto srcInst0 = rrrInst->getOperand(0);
      auto srcInst1 = rrrInst->getOperand(1);
      if (auto liInst = dynamic_cast<riscv::LI *>(srcInst1)) {
        int imm = liInst->getImm();
        auto src = rrrInst->getOperand(0);
        i = reduction(mBlock, i, imm, static_cast<riscv::MachineInst *>(src));
        modified = true;
      } else if (auto liInst = dynamic_cast<riscv::LI *>(srcInst0)) {
        int imm = liInst->getImm();
        auto src = rrrInst->getOperand(1);
        i = reduction(mBlock, i, imm, static_cast<riscv::MachineInst *>(src));
        modified = true;
      }
    }
  }
  return modified;
}

} // namespace pass

#undef MAKE_I32
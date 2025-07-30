#include "riscv/generate_mir.h"

namespace riscv {

using ir::InstKind;
using ir::Instruction;
using std::make_unique;
using std::unique_ptr;
using std::unordered_map;

unique_ptr<MachineFunc> GenerateMIR::funcToMIR(ir::Function *func) {
  auto machineFunc = make_unique<MachineFunc>(func);
  for (auto &block : *func) {
    auto machineBlock =
        make_unique<MachineBlock>(static_cast<ir::BasicBlock *>(block.get()));
    machineFunc->pushBlock(std::move(machineBlock));
    for (auto &instPtr : *block) {
      auto inst = static_cast<Instruction *>(instPtr.get());
      switch (inst->getInstKind()) {
      case InstKind::Alloca:
      case InstKind::Phi:
        continue;
      case InstKind::Binary:
      case InstKind::Branch:
      case InstKind::Call:
      case InstKind::GEP:
      case InstKind::Load:
      case InstKind::Ret:
      case InstKind::Store:
      case InstKind::ICmp:
      case InstKind::FCmp:
      case InstKind::BitCast:
      case InstKind::ZExt:
      case InstKind::SExt:
      case InstKind::SIToFP:
      case InstKind::FPToSI:
      case InstKind::Move:
      default:
        continue;
      }
    }
  }
  return std::move(machineFunc);
}

} // namespace riscv
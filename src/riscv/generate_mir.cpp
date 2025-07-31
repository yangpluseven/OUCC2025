#include "riscv/generate_mir.h"

namespace riscv {

using ir::InstKind;
using ir::Instruction;
using std::make_unique;
using std::unique_ptr;
using std::unordered_map;

unique_ptr<MachineFunc> GenerateMIR::funcToMIR(ir::Function *func) {
  auto machineFunc = make_unique<MachineFunc>(func);
  auto exitBBlock = make_unique<ir::BasicBlock>();
  for (auto &block : *func) {
    auto machineBlock =
        make_unique<MachineBlock>(static_cast<ir::BasicBlock *>(block.get()));
    auto mBlock = machineBlock.get();
    machineFunc->pushBlock(std::move(machineBlock));
    for (auto &instPtr : *block) {
      auto inst = static_cast<Instruction *>(instPtr.get());
      switch (inst->getInstKind()) {
      case InstKind::Alloca:
      case InstKind::Phi:
        continue;
      case InstKind::Binary:
        machineFunc->binary(static_cast<ir::BinaryInst *>(inst), mBlock);
        continue;
      case InstKind::Branch:
        machineFunc->branch(static_cast<ir::BranchInst *>(inst), mBlock);
        continue;
      case InstKind::Call: {
        int paramNum =
            machineFunc->call(static_cast<ir::CallInst *>(inst), mBlock);
        machineFunc->maxFuncParamNum =
            std::max(machineFunc->maxFuncParamNum, paramNum);
        continue;
      }
      case InstKind::GEP:
        machineFunc->gep(static_cast<ir::GetElementPtrInst *>(inst), mBlock);
        continue;
      case InstKind::Load:
        machineFunc->load(static_cast<ir::LoadInst *>(inst), mBlock);
        continue;
      case InstKind::Ret:
        machineFunc->ret(static_cast<ir::RetInst *>(inst), mBlock,
                         exitBBlock.get());
        continue;
      case InstKind::Store:
        machineFunc->store(static_cast<ir::StoreInst *>(inst), mBlock);
        continue;
      case InstKind::ICmp:
        machineFunc->icmp(static_cast<ir::CmpInst *>(inst), mBlock);
        continue;
      case InstKind::FCmp:
        machineFunc->fcmp(static_cast<ir::CmpInst *>(inst), mBlock);
        continue;
      case InstKind::BitCast:
        machineFunc->bitcast(static_cast<ir::CastInst *>(inst), mBlock);
        continue;
      case InstKind::ZExt:
        machineFunc->zext(static_cast<ir::CastInst *>(inst), mBlock);
        continue;
      case InstKind::SExt:
        machineFunc->sext(static_cast<ir::CastInst *>(inst), mBlock);
        continue;
      case InstKind::SIToFP:
        machineFunc->sitofp(static_cast<ir::CastInst *>(inst), mBlock);
        continue;
      case InstKind::FPToSI:
        machineFunc->fptosi(static_cast<ir::CastInst *>(inst), mBlock);
        continue;
      case InstKind::Move:
        // TODO Move is used to handle phi nodes, not supported right now
      default:
        throw std::runtime_error(
            "Unsupported instruction kind in MIR generation: " +
            std::to_string(static_cast<int>(inst->getInstKind())));
      }
    }
  }
  auto exitMBlock = make_unique<MachineBlock>(exitBBlock.get());
  machineFunc->pushBlock(std::move(exitMBlock));
  return std::move(machineFunc);
}

} // namespace riscv
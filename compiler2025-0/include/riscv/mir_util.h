#ifndef RISCV_MIR_UTIL_H
#define RISCV_MIR_UTIL_H

#include "riscv/machine_func.h"
#include "riscv/machine_insts.h"
#include <bitset>
#include <limits>

#define MAKE_I32 std::make_unique<ir::BasicType>(ir::BasicKind::I32)
#define MAKE_F32 std::make_unique<ir::BasicType>(ir::BasicKind::F32)

namespace riscv {

MachineInst *loadImmI(MachineBlock *block, int imm) {
  auto inst = block->pushInstruction(std::make_unique<LI>(MAKE_I32, imm));
  return static_cast<MachineInst *>(inst);
}

MachineInst *loadImmF(MachineBlock *block, int imm) {
  auto tmp = block->pushInstruction(std::make_unique<LI>(MAKE_I32, imm));
  auto inst =
      block->pushInstruction(std::make_unique<RR>(RROp::MV, MAKE_F32, tmp));
  return static_cast<MachineInst *>(inst);
}

MachineInst *loadImmI(MachineBlock *block, float imm) {
  return loadImmI(block, *reinterpret_cast<int *>(&imm));
}

MachineInst *loadImmF(MachineBlock *block, float imm) {
  return loadImmF(block, *reinterpret_cast<int *>(&imm));
}

int bitcount(int x) { return static_cast<int>(std::bitset<32>(x).count()); }

int leadingZeros(int x) {
  constexpr int bitSize = std::numeric_limits<int>::digits + 1;
  if (x == 0) {
    return bitSize;
  }
  std::bitset<bitSize> bits(x);
  int count = 0;
  for (int i = bitSize - 1; i >= 0; --i) {
    if (bits[i] == 0) {
      count++;
    } else {
      break;
    }
  }
  return count;
}

int trailingZeros(int x) {
  constexpr int bitSize = std::numeric_limits<int>::digits + 1;
  if (x == 0) {
    return bitSize;
  }
  std::bitset<bitSize> bits(x);
  int count = 0;
  for (int i = 0; i < bitSize; ++i) {
    if (bits[i] == 0) {
      count++;
    } else {
      break;
    }
  }
  return count;
}

MachineInst *addRegImmF(MachineBlock *block, MachineInst *src, float imm) {
  auto inst = loadImmF(block, imm);
  return addRegRegF(block, src, inst);
}

MachineInst *addRegImmI(MachineBlock *block, MachineInst *src, int imm) {
  if (imm >= -2048 && imm < 2048) {
    // Use ADDI
    auto inst = block->pushInstruction(
        std::make_unique<RRI>(RRIOp::ADDI, MAKE_I32, src, imm));
    return static_cast<MachineInst *>(inst);
  }
  auto inst = loadImmI(block, imm);
  return addRegRegI(block, src, inst);
}

MachineInst *addRegRegF(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1) {
  auto inst = block->pushInstruction(
      std::make_unique<RRR>(RRROp::ADD, MAKE_F32, src0, src1));
  return static_cast<MachineInst *>(inst);
}

MachineInst *addRegRegI(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1) {
  auto inst = block->pushInstruction(
      std::make_unique<RRR>(RRROp::ADD, MAKE_I32, src0, src1));
  return static_cast<MachineInst *>(inst);
}

MachineInst *divImmRegF(MachineBlock *block, float imm, MachineInst *src) {
  auto inst = loadImmF(block, imm);
  return divRegRegF(block, src, inst);
}

MachineInst *divImmRegI(MachineBlock *block, int imm, MachineInst *src) {
  auto inst = loadImmI(block, imm);
  return divRegRegI(block, src, inst);
}

MachineInst *divRegImmF(MachineBlock *block, MachineInst *src, float imm) {
  auto inst = loadImmF(block, imm);
  return divRegRegF(block, src, inst);
}

MachineInst *divRegImmI(MachineBlock *block, MachineInst *src, int imm) {
  if (imm == 1) {
    return src; // No need to divide by 1
  }
  if (imm == -1) {
    // Use NEG
    auto negInst =
        block->pushInstruction(std::make_unique<RR>(RROp::NEG, MAKE_F32, src));
    return static_cast<MachineInst *>(negInst);
  }
  int div = imm;
  bool isPos = true;
  if (div < 0) {
    isPos = false;
    div = -div;
  }
  int shift = 0;
  while (1L << (shift + 32) <= (0x7fffffffL - 0x80000000L % div) *
                                   (div - (1L << (shift + 32)) % div)) {
    shift++;
  }
  int magic = static_cast<int>((1L << (shift + 32)) / div + 1);
  auto tmp1 = loadImmI(block, magic);
  MachineInst *mid1, *mid2;
  if (magic >= 0) {
    auto tmp2 =
        block->pushInstruction(std::make_unique<RRR>(RRROp::MUL, src, tmp1));
    auto tmp3 = block->pushInstruction(
        std::make_unique<RRI>(RRIOp::SRLI, MAKE_I32, tmp2, 32));
    mid1 = static_cast<MachineInst *>(tmp3);
  } else {
    auto tmp2 =
        block->pushInstruction(std::make_unique<RRR>(RRROp::MUL, src, tmp1));
    auto tmp3 = block->pushInstruction(
        std::make_unique<RRI>(RRIOp::SRLI, MAKE_I32, tmp2, 32));
    auto tmp4 =
        block->pushInstruction(std::make_unique<RRR>(RRROp::ADD, tmp3, src));
    mid1 = static_cast<MachineInst *>(tmp4);
  }
  if (shift != 0) {
    auto tmp2 = block->pushInstruction(
        std::make_unique<RRI>(RRIOp::SRAIW, MAKE_I32, mid1, shift));
    mid2 = static_cast<MachineInst *>(tmp2);
  } else {
    mid2 = mid1; // No shift needed
  }
  if (isPos) {
    auto tmp2 = block->pushInstruction(
        std::make_unique<RRI>(RRIOp::SRLIW, MAKE_I32, src, 31));
    auto tmp1 =
        block->pushInstruction(std::make_unique<RRR>(RRROp::ADDW, mid2, tmp2));
    return static_cast<MachineInst *>(tmp1);
  }
  auto tmp2 = block->pushInstruction(
      std::make_unique<RRI>(RRIOp::SRAIW, MAKE_I32, src, 31));
  auto tmp1 =
      block->pushInstruction(std::make_unique<RRR>(RRROp::SUBW, mid2, tmp2));
  return static_cast<MachineInst *>(tmp1);
}

// TODO
MachineInst *divRegRegF(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1);
MachineInst *divRegRegI(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1);
MachineInst *modImmReg(MachineBlock *block, int imm, MachineInst *src);
MachineInst *modRegReg(MachineBlock *block, MachineInst *src0,
                       MachineInst *src1);
MachineInst *mulRegImmF(MachineBlock *block, MachineInst *src, float imm);
MachineInst *mulRegImmI(MachineBlock *block, MachineInst *src, int imm);
MachineInst *mulRegRegF(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1);
MachineInst *mulRegRegI(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1);
MachineInst *subImmRegF(MachineBlock *block, float imm, MachineInst *src);
MachineInst *subImmRegI(MachineBlock *block, int imm, MachineInst *src);
MachineInst *subRegImmF(MachineBlock *block, MachineInst *src, float imm);
MachineInst *subRegImmI(MachineBlock *block, MachineInst *src, int imm);
MachineInst *subRegRegF(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1);
MachineInst *subRegRegI(MachineBlock *block, MachineInst *src0,
                        MachineInst *src1);

MachineInst *binImmReg(MachineBlock *block, ir::ConstantNumber *imm,
                       MachineInst *src);
MachineInst *binRegImm(MachineBlock *block, MachineInst *src,
                       ir::ConstantNumber *imm);
MachineInst *binRegReg(MachineBlock *block, MachineInst *src0,
                       MachineInst *src1);

} // namespace riscv

#endif
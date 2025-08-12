#include "registers.h"
#include "type.h"

#define DECLARE_INT_REG(name)                                                  \
  MReg *const MReg::name = new MReg(MReg::i32_t.get(), #name)
#define DECLARE_FLOAT_REG(name)                                                \
  MReg *const MReg::name = new MReg(MReg::f32_t.get(), #name)
#define INIT_REG_INST(REG)                                                     \
  MachineInst *const MReg::REG##Inst = new MachineInst(MReg::REG);

namespace riscv {

std::unique_ptr<ir::BasicType> MReg::i32_t =
    std::make_unique<ir::BasicType>(ir::BasicKind::I32);
std::unique_ptr<ir::BasicType> MReg::f32_t =
    std::make_unique<ir::BasicType>(ir::BasicKind::F32);

// int
DECLARE_INT_REG(zero);
DECLARE_INT_REG(ra);
DECLARE_INT_REG(sp);
DECLARE_INT_REG(gp);
DECLARE_INT_REG(tp);
DECLARE_INT_REG(t0);
DECLARE_INT_REG(t1);
DECLARE_INT_REG(t2);
DECLARE_INT_REG(t3);
DECLARE_INT_REG(t4);
DECLARE_INT_REG(t5);
DECLARE_INT_REG(t6);
DECLARE_INT_REG(a0);
DECLARE_INT_REG(a1);
DECLARE_INT_REG(a2);
DECLARE_INT_REG(a3);
DECLARE_INT_REG(a4);
DECLARE_INT_REG(a5);
DECLARE_INT_REG(a6);
DECLARE_INT_REG(a7);
DECLARE_INT_REG(s0);
DECLARE_INT_REG(s1);
DECLARE_INT_REG(s2);
DECLARE_INT_REG(s3);
DECLARE_INT_REG(s4);
DECLARE_INT_REG(s5);
DECLARE_INT_REG(s6);
DECLARE_INT_REG(s7);
DECLARE_INT_REG(s8);
DECLARE_INT_REG(s9);
DECLARE_INT_REG(s10);
DECLARE_INT_REG(s11);

// float
DECLARE_FLOAT_REG(fa0);
DECLARE_FLOAT_REG(fa1);
DECLARE_FLOAT_REG(fa2);
DECLARE_FLOAT_REG(fa3);
DECLARE_FLOAT_REG(fa4);
DECLARE_FLOAT_REG(fa5);
DECLARE_FLOAT_REG(fa6);
DECLARE_FLOAT_REG(fa7);
DECLARE_FLOAT_REG(fs0);
DECLARE_FLOAT_REG(fs1);
DECLARE_FLOAT_REG(fs2);
DECLARE_FLOAT_REG(fs3);
DECLARE_FLOAT_REG(fs4);
DECLARE_FLOAT_REG(fs5);
DECLARE_FLOAT_REG(fs6);
DECLARE_FLOAT_REG(fs7);
DECLARE_FLOAT_REG(fs8);
DECLARE_FLOAT_REG(fs9);
DECLARE_FLOAT_REG(fs10);
DECLARE_FLOAT_REG(fs11);
DECLARE_FLOAT_REG(ft0);
DECLARE_FLOAT_REG(ft1);
DECLARE_FLOAT_REG(ft2);
DECLARE_FLOAT_REG(ft3);
DECLARE_FLOAT_REG(ft4);
DECLARE_FLOAT_REG(ft5);
DECLARE_FLOAT_REG(ft6);
DECLARE_FLOAT_REG(ft7);
DECLARE_FLOAT_REG(ft8);
DECLARE_FLOAT_REG(ft9);
DECLARE_FLOAT_REG(ft10);
DECLARE_FLOAT_REG(ft11);

INIT_REG_INST(zero)
INIT_REG_INST(ra)
INIT_REG_INST(sp)
INIT_REG_INST(gp)
INIT_REG_INST(tp)

INIT_REG_INST(t0)
INIT_REG_INST(t1)
INIT_REG_INST(t2)
INIT_REG_INST(t3)
INIT_REG_INST(t4)
INIT_REG_INST(t5)
INIT_REG_INST(t6)

INIT_REG_INST(a0)
INIT_REG_INST(a1)
INIT_REG_INST(a2)
INIT_REG_INST(a3)
INIT_REG_INST(a4)
INIT_REG_INST(a5)
INIT_REG_INST(a6)
INIT_REG_INST(a7)

INIT_REG_INST(s0)
INIT_REG_INST(s1)
INIT_REG_INST(s2)
INIT_REG_INST(s3)
INIT_REG_INST(s4)
INIT_REG_INST(s5)
INIT_REG_INST(s6)
INIT_REG_INST(s7)
INIT_REG_INST(s8)
INIT_REG_INST(s9)
INIT_REG_INST(s10)
INIT_REG_INST(s11)

INIT_REG_INST(fa0)
INIT_REG_INST(fa1)
INIT_REG_INST(fa2)
INIT_REG_INST(fa3)
INIT_REG_INST(fa4)
INIT_REG_INST(fa5)
INIT_REG_INST(fa6)
INIT_REG_INST(fa7)

INIT_REG_INST(fs0)
INIT_REG_INST(fs1)
INIT_REG_INST(fs2)
INIT_REG_INST(fs3)
INIT_REG_INST(fs4)
INIT_REG_INST(fs5)
INIT_REG_INST(fs6)
INIT_REG_INST(fs7)
INIT_REG_INST(fs8)
INIT_REG_INST(fs9)
INIT_REG_INST(fs10)
INIT_REG_INST(fs11)

INIT_REG_INST(ft0)
INIT_REG_INST(ft1)
INIT_REG_INST(ft2)
INIT_REG_INST(ft3)
INIT_REG_INST(ft4)
INIT_REG_INST(ft5)
INIT_REG_INST(ft6)
INIT_REG_INST(ft7)
INIT_REG_INST(ft8)
INIT_REG_INST(ft9)
INIT_REG_INST(ft10)
INIT_REG_INST(ft11)

const std::vector<MReg *> MReg::iRegs = {
    MReg::a0, MReg::a1, MReg::a2, MReg::a3, MReg::a4,  MReg::a5, MReg::a6,
    MReg::a7, MReg::s0, MReg::s1, MReg::s2, MReg::s3,  MReg::s4, MReg::s5,
    MReg::s6, MReg::s7, MReg::s8, MReg::s9, MReg::s10, MReg::s11};

const std::vector<MReg *> MReg::fRegs = {
    MReg::fa0, MReg::fa1, MReg::fa2, MReg::fa3,  MReg::fa4,
    MReg::fa5, MReg::fa6, MReg::fa7, MReg::fs0,  MReg::fs1,
    MReg::fs2, MReg::fs3, MReg::fs4, MReg::fs5,  MReg::fs6,
    MReg::fs7, MReg::fs8, MReg::fs9, MReg::fs10, MReg::fs11};

const std::vector<MReg *> MReg::iCallerRegs = {MReg::a0, MReg::a1, MReg::a2,
                                               MReg::a3, MReg::a4, MReg::a5,
                                               MReg::a6, MReg::a7};

const std::vector<MReg *> MReg::fCallerRegs = {MReg::fa0, MReg::fa1, MReg::fa2,
                                               MReg::fa3, MReg::fa4, MReg::fa5,
                                               MReg::fa6, MReg::fa7};

const std::vector<MReg *> MReg::iCalleeRegs = {
    MReg::s0, MReg::s1, MReg::s2, MReg::s3, MReg::s4,  MReg::s5,
    MReg::s6, MReg::s7, MReg::s8, MReg::s9, MReg::s10, MReg::s11};

const std::vector<MReg *> MReg::fCalleeRegs = {
    MReg::fs0, MReg::fs1, MReg::fs2, MReg::fs3, MReg::fs4,  MReg::fs5,
    MReg::fs6, MReg::fs7, MReg::fs8, MReg::fs9, MReg::fs10, MReg::fs11};

const std::vector<MachineInst *> MReg::iCallerInsts = {
    MReg::a0Inst, MReg::a1Inst, MReg::a2Inst, MReg::a3Inst,
    MReg::a4Inst, MReg::a5Inst, MReg::a6Inst, MReg::a7Inst};

const std::vector<MachineInst *> MReg::fCallerInsts = {
    MReg::fa0Inst, MReg::fa1Inst, MReg::fa2Inst, MReg::fa3Inst,
    MReg::fa4Inst, MReg::fa5Inst, MReg::fa6Inst, MReg::fa7Inst};

} // namespace riscv

#undef DECLARE_INT_REG
#undef DECLARE_FLOAT_REG

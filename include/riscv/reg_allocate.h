#ifndef RISCV_REG_ALLOCATE_H
#define RISCV_REG_ALLOCATE_H

#include "ir/register.h"
#include "riscv/machine_func.h"
#include "riscv/registers.h"
#include <unordered_map>
#include <unordered_set>

namespace riscv {

class BlockInfo {
private:
  const int _begin, _end;
  std::unordered_set<ir::Reg *> _liveUse, _liveDef;
  std::unordered_set<ir::Reg *> _liveIn, _liveOut;
  std::unordered_set<BlockInfo *> _nexts;

public:
  BlockInfo(int begin, int end) : _begin(begin), _end(end) {}

  void addUse(ir::Reg *reg) { _liveUse.insert(reg); }

  void addDef(ir::Reg *reg) { _liveDef.insert(reg); }

  void addNext(BlockInfo *next) { _nexts.insert(next); }

  void calcIn() {
    _liveIn.clear();
    _liveIn.insert(_liveOut.begin(), _liveOut.end());
    for (const auto def : _liveDef) {
      if (_liveIn.find(def) != _liveIn.end()) {
        _liveIn.erase(def);
      }
    }
    _liveIn.insert(_liveUse.begin(), _liveUse.end());
  }

  void calcOut() {
    for (const auto next : _nexts) {
      _liveOut.insert(next->_liveIn.begin(), next->_liveIn.end());
    }
  }

  bool containsInDef(ir::Reg *reg) const {
    return _liveDef.find(reg) != _liveDef.end();
  }

  int getBegin() const { return _begin; }

  int getEnd() const { return _end; }

  std::unordered_set<ir::Reg *> getRegs() const {
    std::unordered_set<ir::Reg *> regs;
    regs.insert(_liveUse.begin(), _liveUse.end());
    regs.insert(_liveDef.begin(), _liveDef.end());
    regs.insert(_liveIn.begin(), _liveIn.end());
    regs.insert(_liveOut.begin(), _liveOut.end());
    return std::move(regs);
  }

  std::unordered_set<ir::Reg *> &getOut() { return _liveOut; }

  size_t sizeOfInOut() const { return _liveIn.size() + _liveOut.size(); }
};

class FuncRegAlloc {
private:
  MachineFunc *_func;
  std::vector<MReg *> _iCallerRegs;
  std::vector<MReg *> _fCallerRegs;
  std::vector<MReg *> _iCalleeRegs{};
  std::vector<MReg *> _fCalleeRegs{};
  int _funcParamSize{}, _alignSize{}, _spillSize{}, _localSize{};
  int _savedRegSize{}, _callAddrSize{}, _paramInnerSize;

  static void calcInOut(std::vector<BlockInfo *> &blocks);

  std::vector<BlockInfo *> calcBlocks() const;
  std::unordered_map<ir::Reg *, std::unordered_set<ir::Reg *>>
  calcConflictMap();
  std::unordered_map<ir::Reg *, std::unordered_set<int>> calcLifespans();
  void calcUseDef(std::vector<BlockInfo *> &blocks) const;
  std::unordered_map<ir::VReg *, MReg *> calcVRegToMReg();
  void makeFrameInfo();
  void popFrame();
  void pushFrame();
  void replaceFakeMIRs();
  void solveSpill();

public:
  explicit FuncRegAlloc(MachineFunc *func) : _func(func) {
    _iCallerRegs =
        std::vector<MReg *>(MReg::iCallerRegs.begin(),
                            MReg::iCallerRegs.begin() + _func->getICallerNum());
    _fCallerRegs =
        std::vector<MReg *>(MReg::fCallerRegs.begin(),
                            MReg::fCallerRegs.begin() + _func->getFCallerNum());
    _paramInnerSize = (func->getICallerNum() + func->getFCallerNum()) * 8;
  }

  void allocate() {
    // TODO
  }
};

class ModuleRegAlloc {
private:
  std::vector<MachineFunc *> _funcs;

public:
  explicit ModuleRegAlloc(
      const std::unordered_map<std::string, MachineFunc *> &funcs) {
    for (const auto &[name, func] : funcs) {
      this->_funcs.push_back(func);
    }
  }

  void allocate() {
    for (const auto func : _funcs) {
      FuncRegAlloc(func).allocate();
    }
  }
};

} // namespace riscv

#endif
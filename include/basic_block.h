#ifndef IR_BASIC_BLOCK_H
#define IR_BASIC_BLOCK_H

#define FMT_HEADER_ONLY
#include "core.h"
#include "function.h"
#include "instruction.h"
#include "value.h"
#include <string>
#include <vector>

namespace ir {

class FuncBase;
class Function;
class InstBase;
class LoopInfo;

class BlockBase : public Value {
private:
  int _id;
  FuncBase *_function;
  std::vector<std::unique_ptr<InstBase>> _instructions;
  std::vector<std::unique_ptr<InstBase>> _unreachables;

protected:
  // Perhaps we only care about the relative order?
  int indexInFunc = -1;

public:
  LoopInfo *loopInfo = nullptr;

  explicit BlockBase(int id);
  void setFunction(FuncBase *func) { _function = func; }
  FuncBase *getFunction() const { return _function; }
  int getID() const { return _id; }
  virtual std::string getLabel() const = 0;
  // Form the .ll IR string for the whole block, including the label and string
  // for all instructions
  std::string str() const override;

  void setIndexInFunc(int index) { indexInFunc = index; }
  int getIndexInFunc() const { return indexInFunc; }

  bool empty() const { return _instructions.empty(); }
  // Check the last instruction
  bool hasTerminator() const;
  InstBase *pushUnreachable(std::unique_ptr<InstBase> inst);
  InstBase *pushInstruction(std::unique_ptr<InstBase> inst);
  InstBase *insertInstruction(size_t index, std::unique_ptr<InstBase> inst);
  InstBase *getTerminator() const;
  InstBase *getLastInstruction() const;
  InstBase *getInstruction(size_t index) const;
  InstBase *setInstruction(size_t index, std::unique_ptr<InstBase> inst);
  std::unique_ptr<InstBase> eraseInstruction(size_t index);
  std::unique_ptr<InstBase> eraseInstruction(InstBase *inst);
  std::unique_ptr<InstBase> getOwnership(size_t index);
  std::unique_ptr<InstBase> getOwnership(InstBase *inst);
  size_t size() const { return _instructions.size(); }
  void clear() { _instructions.clear(); }
  void clearUnreachables() { _unreachables.clear(); }
  void calcIndexInBlock() const;

  using iterator = std::vector<std::unique_ptr<InstBase>>::iterator;
  using const_iterator = std::vector<std::unique_ptr<InstBase>>::const_iterator;

  InstBase *getInstruction(iterator pos) const;
  // Insert using iterator, can be used in other insert functions
  iterator insertInstruction(iterator pos, std::unique_ptr<InstBase> inst);
  // Erase using iterator, move out the ownership
  std::unique_ptr<InstBase> eraseInstruction(iterator pos);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};

class BasicBlock : public BlockBase {
private:
  static int _counter;

public:
  explicit BasicBlock();
  ValueKind getValueKind() const override { return ValueKind::Block; }
  // Get the LLVM like block label, example: bb0 bb1
  std::string getLabel() const override;
  std::string getName() const override {
    return fmt::format("%{}", getLabel());
  }
};

class LoopInfo {
private:
  int _before;
  int _enter;
  int _leave;
  std::unordered_set<BlockBase *> _loopBody;

public:
  LoopInfo(int enter, int leave) : _enter(enter), _leave(leave) {
    assert(enter > 0 && leave > 0 &&
           "Loop enter and leave indices must be greater than 0");
    assert(enter < leave && "Loop enter index must be less than leave index");
    _before = enter - 1;
  }

  int getBeforeIndex() const { return _before; }
  int getEnterIndex() const { return _enter; }
  int getLeaveIndex() const { return _leave; }
  void calcLoopBody(FuncBase *func);
  bool inLoopBody(BlockBase *block) const {
    return _loopBody.find(block) != _loopBody.end();
  }
};

} // namespace ir

#endif // IR_BASIC_BLOCK_H

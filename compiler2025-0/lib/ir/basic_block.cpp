#include "ir/basic_block.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include <cassert>
#include <sstream>

namespace ir {

int BasicBlock::_counter = 0;

BasicBlock::BasicBlock(Function *func)
    : Value(BasicType::get(BasicKind::VOID)), _id(_counter++), _function(func) {
}

bool BasicBlock::empty() const { return _instructions.empty(); }

bool BasicBlock::hasTerminator() const {
  return !empty() && _instructions.back()->isTerminator();
}

void BasicBlock::pushInstruction(std::unique_ptr<Instruction> inst) {
  assert(inst && "Cannot insert nullptr instruction");
  _instructions.push_back(std::move(inst));
}

Instruction *BasicBlock::getTerminator() const {
  if (hasTerminator())
    return _instructions.back().get();
  return nullptr;
}

Instruction *BasicBlock::getInstruction(size_t index) const {
  assert(index < _instructions.size());
  return _instructions[index].get();
}

void BasicBlock::insertInstruction(size_t index,
                                   std::unique_ptr<Instruction> inst) {
  assert(index <= _instructions.size());
  _instructions.insert(_instructions.begin() + index, std::move(inst));
}

std::unique_ptr<Instruction> BasicBlock::eraseInstruction(size_t index) {
  assert(index < _instructions.size());
  auto it = _instructions.begin() + index;
  std::unique_ptr<Instruction> erased = std::move(*it);
  _instructions.erase(it);
  return erased;
}

std::string BasicBlock::str() const {
  std::ostringstream oss;
  oss << "%bb" << _id;
  return oss.str();
}

Instruction *BasicBlock::getInstruction(iterator pos) const {
  return pos->get();
}

BasicBlock::iterator
BasicBlock::insertInstruction(iterator pos, std::unique_ptr<Instruction> inst) {
  return _instructions.insert(pos, std::move(inst));
}

std::unique_ptr<Instruction> BasicBlock::eraseInstruction(iterator pos) {
  std::unique_ptr<Instruction> erased = std::move(*pos);
  _instructions.erase(pos);
  return erased;
}

BasicBlock::iterator BasicBlock::begin() { return _instructions.begin(); }

BasicBlock::iterator BasicBlock::end() { return _instructions.end(); }

BasicBlock::const_iterator BasicBlock::begin() const {
  return _instructions.begin();
}

BasicBlock::const_iterator BasicBlock::end() const {
  return _instructions.end();
}

BasicBlock::const_iterator BasicBlock::cbegin() const {
  return _instructions.cbegin();
}

BasicBlock::const_iterator BasicBlock::cend() const {
  return _instructions.cend();
}

} // namespace ir

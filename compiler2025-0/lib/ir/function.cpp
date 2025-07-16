#include "ir/function.h"
#include "ir/basic_block.h"
#include <cassert>
#include <sstream>

namespace ir {

std::string Argument::getSSAName() const { return "%" + _name; }

std::string Argument::str() const { return getType()->str() + getSSAName(); }

void Function::addArg(std::unique_ptr<Argument> arg) {
  assert(arg && "Cannot add nullptr argument");
  _args.push_back(std::move(arg));
}

std::vector<Argument *> Function::getArgs() const {
  std::vector<Argument *> result;
  result.reserve(_args.size());
  for (const auto &arg : _args) {
    result.push_back(arg.get());
  }
  return result;
}

void Function::pushBlock(std::unique_ptr<BasicBlock> block) {
  assert(block && "Cannot push nullptr block");
  _blocks.push_back(std::move(block));
}

BasicBlock *Function::getBlock(size_t index) const {
  assert(index < _blocks.size() && "Block index out of bounds");
  return _blocks[index].get();
}

BasicBlock *Function::getEntryBlock() const {
  if (_blocks.empty())
    return nullptr;
  return _blocks.front().get();
}

std::unique_ptr<BasicBlock> Function::eraseBlock(size_t index) {
  assert(index < _blocks.size() && "Block index out of bounds");
  auto it = _blocks.begin() + index;
  std::unique_ptr<BasicBlock> removed = std::move(*it);
  _blocks.erase(it);
  return removed;
}

std::string Function::getRawName() const { return _name; }

std::string Function::str() const {
  bool isDeclare = empty();
  std::ostringstream oss;
  std::ostringstream args;

  args << "(";
  for (size_t i = 0; i < _args.size(); ++i) {
    if (i > 0)
      args << ", ";
    if (isDeclare)
      args << _args[i]->getType()->str();
    else
      args << _args[i]->str();
  }
  args << ")";

  if (isDeclare)
    oss << "declare ";
  else
    oss << "define ";

  oss << getType()->str() << " @" << _name << args.str();

  if (isDeclare)
    return oss.str() + "\n";

  oss << " {\n";
  for (const auto &block : _blocks) {
    oss << block->str();
  }
  oss << "}\n";

  return oss.str();
}

Function::iterator Function::begin() { return _blocks.begin(); }

Function::iterator Function::end() { return _blocks.end(); }

Function::const_iterator Function::begin() const { return _blocks.begin(); }

Function::const_iterator Function::end() const { return _blocks.end(); }

Function::const_iterator Function::cbegin() const { return _blocks.cbegin(); }

Function::const_iterator Function::cend() const { return _blocks.cend(); }

Function::iterator Function::insertBlock(iterator pos,
                                         std::unique_ptr<BasicBlock> block) {
  assert(block && "Cannot insert nullptr block");
  return _blocks.insert(pos, std::move(block));
}

std::unique_ptr<BasicBlock> Function::eraseBlock(iterator pos) {
  std::unique_ptr<BasicBlock> removed = std::move(*pos);
  _blocks.erase(pos);
  return removed;
}

BasicBlock *Function::getBlock(iterator pos) const { return pos->get(); }

} // namespace ir

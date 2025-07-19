#include "ir/module.h"

namespace ir {

void Module::addGlobal(std::unique_ptr<GlobalVariable> global) {
  globals.emplace(global->getRawName(), std::move(global));
}

void Module::addFunction(std::unique_ptr<Function> function) {
  functions.emplace(function->getRawName(), std::move(function));
}

bool Module::hasGlobal() const { return !globals.empty(); }

bool Module::hasFunction() const { return !functions.empty(); }

GlobalVariable *Module::getGlobal(const std::string &name) {
  auto it = globals.find(name);
  return it != globals.end() ? it->second.get() : nullptr;
}

Function *Module::getFunction(const std::string &name) {
  auto it = functions.find(name);
  return it != functions.end() ? it->second.get() : nullptr;
}

std::vector<GlobalVariable *> Module::getGlobals() {
  std::vector<GlobalVariable *> result;
  result.reserve(globals.size());
  for (auto &[name, ptr] : globals) {
    result.push_back(ptr.get());
  }
  return result;
}

std::vector<Function *> Module::getFunctions() {
  std::vector<Function *> result;
  result.reserve(functions.size());
  for (auto &[name, ptr] : functions) {
    result.push_back(ptr.get());
  }
  return result;
}

} // namespace ir

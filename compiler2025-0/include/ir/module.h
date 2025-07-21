#ifndef IR_MODULE_H
#define IR_MODULE_H

#include "ir/function.h"
#include "ir/global_variable.h"
#include <unordered_map>
#include <vector>

namespace ir {

class Module {
private:
  std::unordered_map<std::string, std::unique_ptr<GlobalVariable>> globals;
  std::unordered_map<std::string, std::unique_ptr<Function>> functions;

public:
  Module() = default;

  void addGlobal(std::unique_ptr<GlobalVariable> global);
  void addFunction(std::unique_ptr<Function> function);

  bool hasGlobal() const;
  bool hasFunction() const;

  GlobalVariable *getGlobal(const std::string &name);
  Function *getFunction(const std::string &name);

  size_t numGlobals() const { return globals.size(); }
  size_t numFunctions() const { return functions.size(); }

  // Return a viewport instead of the actual ownership
  std::vector<GlobalVariable *> getGlobals();
  // Return a viewport instead of the actual ownership
  std::vector<Function *> getFunctions();
};

} // namespace ir

#endif // IR_MODULE_H

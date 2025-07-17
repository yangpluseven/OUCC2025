#ifndef PARSER_SYMBOLTABLE_H
#define PARSER_SYMBOLTABLE_H

#include "ir/constant.h"
#include "ir/function.h"
#include "ir/global_variable.h"
#include "ir/instructions.h"
#include "ir/number.h"
#include "ir/value.h"
#include <cassert>
#include <list>
#include <map>
#include <stdexcept>
#include <unordered_map>

class SymbolTable {
private:
  std::list<std::unordered_map<std::string, ir::Value *>> _table;

  [[nodiscard]] ir::Value *getItem(const std::string &name) const;

  static std::map<int, Number> submap(const std::map<int, Number> &values,
                                      int fromKey, int toKey);

  static std::unique_ptr<ir::Constant>
  fuseConst(std::unique_ptr<ir::Type> type, const std::map<int, Number> &values,
            int base);

public:
  [[nodiscard]] size_t size() const { return _table.size(); }

  void out() { _table.pop_front(); }

  void in() { _table.emplace_front(); }

  [[nodiscard]] ir::Value *getData(const std::string &name) const {
    return getItem(name);
  }

  [[nodiscard]] ir::Function *getFunction(const std::string &name) const;

  std::unique_ptr<ir::Function> makeFunc(std::unique_ptr<ir::Type> type,
                                         const std::string &name);

  std::unique_ptr<ir::GlobalVariable> makeGlobal(bool isConst,
                                                 std::unique_ptr<ir::Type> type,
                                                 const std::string &name,
                                                 Number &value);

  std::unique_ptr<ir::GlobalVariable> makeGlobal(bool isConst,
                                                 std::unique_ptr<ir::Type> type,
                                                 const std::string &name,
                                                 std::map<int, Number> &values);

  std::unique_ptr<ir::AllocaInst> makeLocal(ir::BasicBlock *block,
                                            std::unique_ptr<ir::Type> type,
                                            const std::string &name);

  std::unique_ptr<ir::AllocaInst> makeLocal(ir::BasicBlock *block,
                                            std::unique_ptr<ir::Type> type,
                                            const std::string &name,
                                            const std::vector<int> &dimensions);

  std::unique_ptr<ir::Argument> makeArgument(std::unique_ptr<ir::Type> type,
                                             const std::string &name);
};

#endif
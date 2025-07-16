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

  [[nodiscard]] ir::Value *get(const std::string &name) const {
    for (auto item : _table) {
      if (item.find(name) != item.end())
        return item[name];
    }
    throw std::runtime_error("Undefined variable: " + name);
  }

  static std::map<int, Number> submap(const std::map<int, Number> &values,
                                      int fromKey, int toKey) {
    std::map<int, Number> sub;
    auto lower = values.lower_bound(fromKey);
    auto upper = values.upper_bound(toKey);

    for (; lower != upper; ++lower)
      sub.insert(*lower);

    return sub;
  }

  static std::unique_ptr<ir::Constant>
  fuseConst(ir::Type *type, const std::map<int, Number> &values, int base) {
    if (dynamic_cast<ir::BasicType *>(type))
      if (values.find(base) != values.end())
        return std::make_unique<ir::ConstantNumber>(values.at(base));
      else
        return std::make_unique<ir::ConstantNumber>(Number(0));

    if (values.empty())
      return std::make_unique<ir::ConstantZero>(type);

    auto arrayType = dynamic_cast<ir::ArrayType *>(type);
    size_t size = 1;
    for (auto i : arrayType->getDimensions())
      size *= i;

    std::vector<std::unique_ptr<ir::Constant>> array;
    for (size_t i = base; i < base + size; i += size / arrayType->getLength())
      array.push_back(
          fuseConst(arrayType->getBaseType(),
                    submap(values, static_cast<int>(i),
                           static_cast<int>(i + size / arrayType->getLength())),
                    static_cast<int>(i)));
    return std::make_unique<ir::ConstantArray>(arrayType, array);
  }

public:
  [[nodiscard]] ir::Value *getData(const std::string &name) const {
    return get(name);
  }

  [[nodiscard]] ir::Function *getFunc(const std::string &name) const {
    auto symbol = get(name);
    if (auto func = dynamic_cast<ir::Function *>(symbol))
      return func;
    throw std::runtime_error("Undefined function: " + name);
  }

  void in() { _table.emplace_front(); }

  ir::Function *makeFunc(std::unique_ptr<ir::Type> type,
                         const std::string &name) {
    auto func = new ir::Function(std::move(type), name);
    _table.back()[name] = func;
    return func;
  }

  ir::GlobalVariable *makeGlobal(bool isConst, std::unique_ptr<ir::Type> type,
                                 const std::string &name, const Number &value) {
    assert(type->isBasic());
    Number realVal(0);
    auto basicType = static_cast<ir::BasicType *>(type.get())->getBasicKind();
    switch (basicType) {
    case ir::BasicKind::I32:
      realVal = Number(value.intValue());
      break;
    case ir::BasicKind::F32:
      realVal = Number(value.floatValue());
      break;
    default:
      throw std::runtime_error("Unsupported type in makeGlobal");
    }

    auto symbol =
        new ir::GlobalVariable(std::move(type), name, isConst,
                               std::make_unique<ir::ConstantNumber>(realVal));
    _table.front()[name] = symbol;
    return symbol;
  }

  ir::GlobalVariable *makeGlobal(bool isConst, std::unique_ptr<ir::Type> type,
                                 const std::string &name,
                                 const std::map<int, Number> &values) {
    ir::BasicType *rootType;
    if (type->isArray()) {
      rootType =
          static_cast<ir::ArrayType *>(type.get())->getInnermostElementType();
    } else {
      rootType = static_cast<ir::BasicType *>(type.get());
    }
    ir::BasicKind basicKind = rootType->getBasicKind();
    for (auto i : values) {
      switch (basicKind) {
      case ir::BasicKind::I32:
        i.second = Number(i.second.intValue());
        break;
      case ir::BasicKind::F32:
        i.second = Number(i.second.floatValue());
        break;
      default:
        throw std::runtime_error("Unsupported type in makeGlobal");
      }
    }

    auto symbol =
        new ir::GlobalVariable(std::move(type), name, isConst,
                               std::move(fuseConst(type.get(), values, 0)));
    _table.front()[name] = symbol;
    return symbol;
  }

  [[nodiscard]] size_t size() const { return _table.size(); }

  std::unique_ptr<ir::AllocaInst>
  makeLocal(ir::BasicBlock *block, ir::Type *type, const std::string &name) {
    auto symbol = std::make_unique<ir::AllocaInst>(type, block);
    _table.front()[name] = symbol.get();
    return std::move(symbol);
  }

  std::unique_ptr<ir::AllocaInst>
  makeLocal(ir::BasicBlock *block, std::unique_ptr<ir::Type> type,
            const std::string &name, const std::vector<int> &dimensions) {
    for (int i = static_cast<int>(dimensions.size() - 1); i >= 0; i--)
      type = std::make_unique<ir::ArrayType>(std::move(type), dimensions[i]);

    auto allocaInst = std::make_unique<ir::AllocaInst>(type, block);
    _table.front()[name] = allocaInst.get();
    return std::move(allocaInst);
  }

  std::unique_ptr<ir::Argument> makeArg(std::unique_ptr<ir::Type> type,
                                        const std::string &name) {
    auto arg = std::make_unique<ir::Argument>(std::move(type), name);
    _table.front()[name] = arg.get();
    return std::move(arg);
  }

  void out() { _table.pop_front(); }
};

#endif
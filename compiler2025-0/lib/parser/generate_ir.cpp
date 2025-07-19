#include "parser/generate_ir.h"
#include "ir/instructions.h"
#include "ir/number.h"
#include <algorithm>
using namespace ir;

BasicKind _curTypeKind;
bool _isConst;
// bool _useConst = false;
std::vector<std::unique_ptr<Argument>> _arguments;
Value *_retVal;
BasicBlock *_retBlock;
bool _isNewFunction = false;
bool _isAssign = false;
Function *_curFunction = nullptr;
Value *_curVal = nullptr;
BasicBlock *_entryBlock = nullptr;
BasicBlock *_condBlock = nullptr;
BasicBlock *_trueBlock = nullptr;
BasicBlock *_falseBlock = nullptr;
BasicBlock *_breakBlock = nullptr;
bool _hasBranch = false;

Module *_module;
BasicBlock *_curBlock;
SymbolTable *_symbolTable;
std::unordered_map<Argument *, AllocaInst *> _argToAllocaMap;

void GenerateIR::makeInitVal(std::vector<int> &dimensions,
                             std::map<int, AddExp *> &exps, int base,
                             const InitVal *initVal) {
  int offset = 0;
  for (const auto &child : initVal->initValList) {
    if (child->exp == nullptr) {
      int size = 1;
      for (int i = 1; i < dimensions.size(); i++)
        size *= dimensions[i];
      offset = (offset + size - 1) / size * size;
      std::vector<int> newDimensions(dimensions.begin() + 1, dimensions.end());
      makeInitVal(newDimensions, exps, base + offset, child.get());
      offset += size;
    } else {
      exps[base + offset] = child->exp.get();
      offset++;
    }
  }
}

BasicKind GenerateIR::autoTypePromotion(BasicKind type1, BasicKind type2) {
  if (type1 == BasicKind::F32 || type2 == BasicKind::F32) {
    return BasicKind::F32;
  }
  if (type1 == BasicKind::I32 || type2 == BasicKind::I32) {
    return BasicKind::I32;
  }
  return BasicKind::I1;
}

// The return value of this funciton should not be used to make another unique
// pointer or deleted
Value *GenerateIR::typeConversion(Value *value, BasicKind targetType) {
  if (!value->getType()->isBasic()) {
    throw std::runtime_error("Not a basic type in typeConversion");
  }
  auto type = static_cast<BasicType *>(value->getType())->getBasicKind();
  if (type == targetType) {
    return value;
  }
  if (value->isConst()) {
    auto constant = static_cast<ConstantNumber *>(value);
    switch (targetType) {
    case BasicKind::I32:
      return new ConstantNumber(Number(constant->intValue()));
    case BasicKind::I1:
      return new ConstantNumber(constant->intValue() != 0);
    case BasicKind::F32:
      return new ConstantNumber(Number(constant->floatValue()));
    }
  }
  Instruction *inst;
  switch (targetType) {
  case BasicKind::I1:
    switch (type) {
    case BasicKind::I1:
      return value;
    case BasicKind::I32:
      inst = new CmpInst(_curBlock, CmpOp::NE, value,
                         new ConstantNumber(Number(0)));

    case BasicKind::F32:
      inst = new CmpInst(_curBlock, CmpOp::UNE, value,
                         new ConstantNumber(Number(0.0f)));
    }
  case BasicKind::I32:
    switch (type) {
    case BasicKind::I1:
      inst = new CastInst(std::make_unique<BasicType>(BasicKind::I32),
                          _curBlock, CastOp::ZExt, value);
    case BasicKind::I32:
      return value;
    case BasicKind::F32:
      inst = new CastInst(std::make_unique<BasicType>(BasicKind::I32),
                          _curBlock, CastOp::FPToSI, value);
    }
  case BasicKind::F32:
    switch (type) {
    case BasicKind::I1:
      inst = new CastInst(std::make_unique<BasicType>(BasicKind::I32),
                          _curBlock, CastOp::ZExt, value);
      _curBlock->pushInstruction(std::unique_ptr<Instruction>(inst));
      inst = new CastInst(std::make_unique<BasicType>(BasicKind::F32),
                          _curBlock, CastOp::SIToFP, value);
    case BasicKind::I32:
      inst = new CastInst(std::make_unique<BasicType>(BasicKind::F32),
                          _curBlock, CastOp::SIToFP, value);
    case BasicKind::F32:
      return value;
    }
  }
  _curBlock->pushInstruction(std::unique_ptr<Instruction>(inst));
  return inst;
}

void GenerateIR::visit(CompUnit &ast) {
  for (const auto &def : ast.declDefList) {
    def->accept(*this);
  }
}

void GenerateIR::visit(DeclDef &ast) {
  if (ast.decl) {
    ast.decl->accept(*this);
    return;
  }
  ast.funcDef->accept(*this);
}

void GenerateIR::visit(Decl &ast) {
  _isConst = ast.isConst;
  _curTypeKind = ast.bType == BType::INT ? BasicKind::I32 : BasicKind::F32;
  for (auto &def : ast.defList) {
    def->accept(*this);
  }
}

void GenerateIR::handleScalarDef(Def &ast) {
  std::string varName = *ast.id;
  if (_symbolTable->isGlobal() || _isConst) {
    auto number = Number(0);
    if (ast.initVal) {
      ast.initVal->accept(*this);
      number = static_cast<ConstantNumber *>(_curVal)->getValue();
    }
    _module->addGlobal(_symbolTable->makeGlobal(
        _isConst, std::make_unique<BasicType>(_curTypeKind), varName, number));
    return;
  }
  auto allocaInst = _symbolTable->makeLocal(
      _entryBlock, std::make_unique<BasicType>(_curTypeKind), varName);
  auto rawAllocaInst = allocaInst.get();
  _entryBlock->pushInstruction(std::move(allocaInst));
  if (ast.initVal) {
    ast.initVal->accept(*this);
    auto val = typeConversion(_curVal, _curTypeKind);
    _curBlock->pushInstruction(
        std::make_unique<StoreInst>(_curBlock, val, rawAllocaInst));
  }
}

void GenerateIR::handleArrayDef(Def &ast) {
  std::string varName = *ast.id;
  vector<int> dimensions;
  for (auto &exp : ast.arrays) {
    exp->accept(*this);
    auto number = static_cast<ConstantNumber *>(_curVal);
    dimensions.push_back(number->intValue());
  }
  if (_symbolTable->isGlobal() || _isConst) {
    std::map<int, AddExp *> exps;
    if (ast.initVal) {
      makeInitVal(dimensions, exps, 0, ast.initVal.get());
    }
    auto reverseDimensions = dimensions;
    std::reverse(reverseDimensions.begin(), reverseDimensions.end());
    std::unique_ptr<Type> type = std::make_unique<BasicType>(_curTypeKind);
    for (auto dim : reverseDimensions) {
      type = std::make_unique<ArrayType>(std::move(type), dim);
    }

    std::map<int, Number> values;
    for (auto &[index, exp] : exps) {
      exp->accept(*this);
      auto result = static_cast<ConstantNumber *>(_curVal);
      values.insert(std::make_pair(index, result->getValue()));
    }

    _module->addGlobal(
        _symbolTable->makeGlobal(_isConst, std::move(type), varName, values));
    return;
  }
  auto allocaInst = _symbolTable->makeLocal(
      _entryBlock, std::make_unique<BasicType>(_curTypeKind), varName,
      dimensions);
  auto rawAllocaInst = allocaInst.get();
  _entryBlock->pushInstruction(std::move(allocaInst));
  if (ast.initVal) {
    std::map<int, AddExp *> exps;
    makeInitVal(dimensions, exps, 0, ast.initVal.get());
    auto castInst = std::make_unique<CastInst>(
        std::make_unique<PointerType>(
            std::make_unique<BasicType>(BasicKind::I32)),
        _curBlock, CastOp::BitCast, rawAllocaInst);
    auto rawCastInst = castInst.get();
    _curBlock->pushInstruction(std::move(castInst));
    int x = 4;
    for (auto dim : dimensions) {
      x *= dim;
    }
    std::vector<Value *> args{rawCastInst, new ConstantNumber(Number(0)),
                              new ConstantNumber(Number(x))};
    // Try memclr maybe (ATTENTION)
    _curBlock->pushInstruction(std::make_unique<CallInst>(
        _curBlock, _symbolTable->getFunction("memset"), args));

    for (auto &[index, exp] : exps) {
      exp->accept(*this);
      auto val = typeConversion(_curVal, _curTypeKind);
      Value *ptr = rawAllocaInst;
      for (int j = 0; j < dimensions.size(); j++) {
        int num = 1;
        for (int k = j + 1; k < dimensions.size(); k++) {
          num *= dimensions[k];
        }
        int idx = index / num % dimensions[j];
        vector<Value *> indices{new ConstantNumber(Number(0)),
                                new ConstantNumber(Number(0))};
        auto gepInst =
            std::make_unique<GetElementPtrInst>(_curBlock, ptr, indices);
        ptr = gepInst.get();
        _curBlock->pushInstruction(std::move(gepInst));
      }
      _curBlock->pushInstruction(
          std::make_unique<StoreInst>(_curBlock, val, ptr));
    }
  }
}

void GenerateIR::visit(Def &ast) {
  if (ast.arrays.empty()) {
    handleScalarDef(ast);
  } else {
    handleArrayDef(ast);
  }
}

// This is used to handle scalar init value, see makeInitVal() also
void GenerateIR::visit(InitVal &ast) {
  if (ast.exp) {
    ast.exp->accept(*this);
  }
}

void GenerateIR::visit(FuncDef &ast) {
  _isNewFunction = true;
  _arguments.clear();
}

// TODO: Need more type check and exception handling
void GenerateIR::visit(AddExp &ast) {
  if (ast.addExp == nullptr) {
    ast.mulExp->accept(*this);
    return;
  }
  ast.addExp->accept(*this);
  Value *val1 = _curVal;
  ast.mulExp->accept(*this);
  Value *val2 = _curVal;

  if (val1->isConst() && val2->isConst()) {
    auto number1 = static_cast<ConstantNumber *>(val1);
    auto number2 = static_cast<ConstantNumber *>(val2);
    switch (ast.op) {
    case AddOp::ADD:
      _curVal = new ConstantNumber(*number1 + *number2);
      break;
    case AddOp::MINUS:
      _curVal = new ConstantNumber(*number1 - *number2);
      break;
    }
  } else {
    auto type1 = static_cast<BasicType *>(val1->getType())->getBasicKind();
    auto type2 = static_cast<BasicType *>(val2->getType())->getBasicKind();
    BasicKind targetType = autoTypePromotion(type1, type2);
    val1 = typeConversion(val1, targetType);
    val2 = typeConversion(val2, targetType);
    BinaryOp op;
    switch (ast.op) {
    case AddOp::ADD:
      switch (targetType) {
      case BasicKind::I32:
        op = BinaryOp::ADD;
        break;
      case BasicKind::F32:
        op = BinaryOp::FADD;
        break;
      }
      break;
    case AddOp::MINUS:
      switch (targetType) {
      case BasicKind::I32:
        op = BinaryOp::SUB;
        break;
      case BasicKind::F32:
        op = BinaryOp::FSUB;
        break;
      }
      break;
    }
    auto inst = new BinaryInst(_curBlock, op, val1, val2);
    _curBlock->pushInstruction(std::unique_ptr<Instruction>(inst));
    _curVal = inst;
  }
}

// TODO: Need more type check and exception handling
void GenerateIR::visit(MulExp &ast) {
  if (ast.mulExp == nullptr) {
    ast.unaryExp->accept(*this);
    return;
  }
  ast.mulExp->accept(*this);
  Value *val1 = _curVal;
  ast.unaryExp->accept(*this);
  Value *val2 = _curVal;

  if (val1->isConst() && val2->isConst()) {
    auto number1 = static_cast<ConstantNumber *>(val1);
    auto number2 = static_cast<ConstantNumber *>(val2);
    switch (ast.op) {
    case MulOp::MUL:
      _curVal = new ConstantNumber((*number1) * (*number2));
      break;
    case MulOp::DIV:
      _curVal = new ConstantNumber((*number1) / (*number2));
      break;
    case MulOp::MOD:
      _curVal = new ConstantNumber((*number1) % (*number1));
      break;
    }
  } else {
    auto type1 = static_cast<BasicType *>(val1->getType())->getBasicKind();
    auto type2 = static_cast<BasicType *>(val2->getType())->getBasicKind();
    BasicKind targetType = autoTypePromotion(type1, type2);
    val1 = typeConversion(val1, targetType);
    val2 = typeConversion(val2, targetType);
    BinaryOp op;
    switch (ast.op) {
    case MulOp::MUL:
      switch (targetType) {
      case BasicKind::I32:
        op = BinaryOp::MUL;
        break;
      case BasicKind::F32:
        op = BinaryOp::FMUL;
        break;
      }
      break;
    case MulOp::DIV:
      switch (targetType) {
      case BasicKind::I32:
        op = BinaryOp::SDIV;
        break;
      case BasicKind::F32:
        op = BinaryOp::FDIV;
        break;
      }
      break;
    case MulOp::MOD:
      switch (targetType) {
      case BasicKind::I32:
        op = BinaryOp::SREM;
        break;
      }
      break;
    }
    auto inst = new BinaryInst(_curBlock, op, val1, val2);
    _curBlock->pushInstruction(std::unique_ptr<Instruction>(inst));
    _curVal = inst;
  }
}

// TODO: Need more type check and exception handling
void GenerateIR::visit(UnaryExp &ast) {
  if (ast.primaryExp) {
    ast.primaryExp->accept(*this);
    return;
  }
  if (ast.call) {
    ast.call->accept(*this);
    return;
  }
  ast.unaryExp->accept(*this);
  Value *val = _curVal;
  if (!val->getType()->isBasic()) {
    throw std::runtime_error("Not a basic type in visit(UnaryExp &ast)");
  }
  if (val->isConst()) {
    auto number = static_cast<ConstantNumber *>(val);
    switch (ast.op) {
    case UnaryOp::ADD:
      _curVal = number;
      return;
    case UnaryOp::MINUS:
      _curVal = new ConstantNumber(-(*number));
      return;
    case UnaryOp::NOT:
      _curVal = new ConstantNumber(!(*number));
      return;
    }
  }
  auto type = static_cast<BasicType *>(val->getType())->getBasicKind();
  Instruction *inst;
  switch (ast.op) {
  case UnaryOp::ADD:
    _curVal = val;
    return;
  case UnaryOp::MINUS:
    switch (type) {
    case BasicKind::I1:
      inst = new CastInst(std::make_unique<BasicType>(BasicKind::I32),
                          _curBlock, CastOp::SExt, val);
      break;
    case BasicKind::I32:
      inst = new BinaryInst(_curBlock, BinaryOp::SUB,
                            new ConstantNumber(Number(0)), val);
      break;
    case BasicKind::F32:
      inst = new BinaryInst(_curBlock, BinaryOp::FSUB,
                            new ConstantNumber(Number(0.0f)), val);
      break;
    }
    break;
  case UnaryOp::NOT:
    switch (type) {
    case BasicKind::I1:
      inst = new BinaryInst(_curBlock, BinaryOp::XOR, val,
                            new ConstantNumber(true));
      break;
    case BasicKind::I32:
      inst =
          new CmpInst(_curBlock, CmpOp::EQ, val, new ConstantNumber(Number(0)));
      break;
    case BasicKind::F32:
      inst = new CmpInst(_curBlock, CmpOp::OEQ, val,
                         new ConstantNumber(Number(0.0f)));
      break;
    }
    break;
  }
  _curBlock->pushInstruction(std::unique_ptr<Instruction>(inst));
  _curVal = inst;
}

void GenerateIR::visit(PrimaryExp &ast) {
  if (ast.exp) {
    ast.exp->accept(*this);
    return;
  }
  if (ast.lval) {
    ast.lval->accept(*this);
    return;
  }
  if (ast.number) {
    ast.number->accept(*this);
    return;
  }
}

void GenerateIR::visit(LVal &ast) {}

void GenerateIR::visit(NumberNode &ast) {
  if (ast.isInt) {
    _curVal = new ConstantNumber(ast.intval);
    return;
  }
  _curVal = new ConstantNumber(ast.floatval);
}
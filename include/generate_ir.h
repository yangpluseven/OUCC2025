#include "ast.h"
#include "basic_block.h"
#include "module.h"
#include "symbol_table.h"
#include <queue>
#include <stdexcept>
#include <unordered_map>

class GenerateIR : public ASTVisitor {
private:
  ir::BasicKind _curTypeKind;
  bool _isConst;
  ir::Value *_retVal;
  ir::BasicBlock *_retBlock;
  bool _isRealLVal = false;
  ir::Function *_curFunction = nullptr;
  ir::Value *_curVal = nullptr;
  ir::BasicBlock *_entryBlock = nullptr;
  ir::BasicBlock *_condBlock = nullptr;
  ir::BasicBlock *_trueBlock = nullptr;
  ir::BasicBlock *_falseBlock = nullptr;
  ir::BasicBlock *_breakBlock = nullptr;

  ir::Module *const _module = new ir::Module();
  SymbolTable *const _symbolTable = new SymbolTable();
  ir::BasicBlock *_curBlock;
  std::unordered_map<ir::Argument *, ir::AllocaInst *> _argToAllocaMap;

  void initBuiltInFuncs();

  void initSysCalls();

  void processCond(ir::Value *value);

  void makeInitVal(std::vector<int> &dimensions, std::map<int, AddExpNode *> &exps,
                   int base, const InitValNode *initVal);

  ir::Value *typeConversion(ir::Value *value, ir::BasicKind targetType);

  static ir::BasicKind autoTypePromotion(ir::BasicKind type1,
                                         ir::BasicKind type2);

  void handleScalarDef(DefNode &ast);

  void handleArrayDef(DefNode &ast);

  void handleScalarVar(LValNode &ast);

  void handleArrayVar(LValNode &ast);

  void handleAssignStmt(StmtNode &ast);

  void handleIfElseStmt(IfStmtNode &ast);

  std::unique_ptr<ir::BasicType> handleType(BType &type);

public:
  GenerateIR() {
    _symbolTable->in();
    initBuiltInFuncs();
    initSysCalls();
  }

  void checkTerminator();

  ir::Module *getModule() const { return _module; }

  void visit(CompUnitNode &ast) override;

  void visit(DeclNode &ast) override;

  void visit(DefNode &ast) override;

  void visit(InitValNode &ast) override;

  void visit(FuncDefNode &ast) override;

  void visit(FuncFParamNode &ast) override;

  void visit(BlockNode &ast) override;

  void visit(BlockItemNode &ast) override;

  void visit(StmtNode &ast) override;

  void visit(ReturnStmtNode &ast) override;

  void visit(IfStmtNode &ast) override;

  void visit(WhileStmtNode &ast) override;

  void visit(AddExpNode &ast) override;

  void visit(MulExpNode &ast) override;

  void visit(UnaryExpNode &ast) override;

  void visit(PrimaryExpNode &ast) override;

  void visit(LValNode &ast) override;

  void visit(NumberNode &ast) override;

  void visit(CallNode &ast) override;

  void visit(RelExpNode &ast) override;

  void visit(EqExpNode &ast) override;

  void visit(LAndExpNode &ast) override;

  void visit(LOrExpNode &ast) override;
};

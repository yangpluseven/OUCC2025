#include "ir/basic_block.h"
#include "ir/module.h"
#include "parser/ast.h"
#include "parser/symbol_table.h"
#include <queue>
#include <stdexcept>
#include <unordered_map>

class GenerateIR : public ASTVisitor {
private:
  void initBuiltInFuncs();

  void initSysCalls();

  void checkIfIsProcessed();

  void formatLLVM();

  void makeInitVal(std::vector<int> &dimensions, std::map<int, AddExp *> &exps,
                   int base, const InitVal *initVal);

  void processValueCond(ir::Value *value);

  ir::Value *typeConversion(ir::Value *value, ir::BasicKind targetType);

  static ir::BasicKind autoTypePromotion(ir::BasicKind type1,
                                         ir::BasicKind type2);

  void handleScalarDef(Def &ast);

  void handleArrayDef(Def &ast);

  void handleScalarVar(LVal &ast);

  void handleArrayVar(LVal &ast);

public:
  GenerateIR() {
    // TODO: Init builtin functions and system calls here
  }

  void visit(CompUnit &ast) override;
  void visit(DeclDef &ast) override;
  void visit(Decl &ast) override;
  void visit(Def &ast) override;
  void visit(InitVal &ast) override;
  void visit(FuncDef &ast) override;
  void visit(FuncFParam &ast) override;
  void visit(Block &ast) override;
  void visit(BlockItem &ast) override;
  void visit(Stmt &ast) override;
  void visit(ReturnStmt &ast) override;
  void visit(IfStmt &ast) override;
  void visit(WhileStmt &ast) override;
  void visit(AddExp &ast) override;
  void visit(MulExp &ast) override;
  void visit(UnaryExp &ast) override;
  void visit(PrimaryExp &ast) override;
  void visit(LVal &ast) override;
  void visit(NumberNode &ast) override;
  void visit(Call &ast) override;
  void visit(RelExp &ast) override;
  void visit(EqExp &ast) override;
  void visit(LAndExp &ast) override;
  void visit(LOrExp &ast) override;
};
#pragma once

#include "define.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

class BaseNode;

class CompUnitNode;
class DeclNode;
class DefList;
class DefNode;
class ArrayList;
class InitValList;
class InitValNode;
class FuncDefNode;
class FuncFParamList;
class FuncFParamNode;
class BlockNode;
class BlockItemList;
class BlockItemNode;
class StmtNode;
class ReturnStmtNode;
class IfStmtNode;
class WhileStmtNode;
class LValNode;
class PrimaryExpNode;
class NumberNode;
class UnaryExpNode;
class CallNode;
class FuncCParamList;
class MulExpNode;
class AddExpNode;
class RelExpNode;
class EqExpNode;
class LAndExpNode;
class LOrExpNode;

class ASTVisitor;

class BaseNode {
public:
  virtual void accept(ASTVisitor &visitor) = 0;

  BaseNode() = default;

  virtual ~BaseNode() = default;
};

class CompUnitNode : public BaseNode {
public:
  vector<unique_ptr<DeclNode>> declList;
  vector<unique_ptr<FuncDefNode>> funcDefList;
  void accept(ASTVisitor &visitor) override;
};

class DeclNode final : public BaseNode {
public:
  BType bType = BType::VOID;
  bool isConst = false;
  vector<unique_ptr<DefNode>> defList;
  void accept(ASTVisitor &visitor) override;
};

class DefList {
public:
  vector<unique_ptr<DefNode>> list;
};

class DefNode : public BaseNode {
public:
  unique_ptr<string> id;
  vector<unique_ptr<AddExpNode>> arrays;
  unique_ptr<InitValNode> initVal;
  void accept(ASTVisitor &visitor) override;
};

class ArrayList {
public:
  vector<unique_ptr<AddExpNode>> list;
};

class InitValNode : public BaseNode {
public:
  unique_ptr<AddExpNode> exp;
  vector<unique_ptr<InitValNode>> initValList;
  void accept(ASTVisitor &visitor) override;
};

class InitValList {
public:
  vector<unique_ptr<InitValNode>> list;
};

class FuncDefNode : public BaseNode {
public:
  BType returnType = BType::VOID;
  unique_ptr<string> id;
  vector<unique_ptr<FuncFParamNode>> funcFParamList;
  unique_ptr<BlockNode> block = nullptr;
  void accept(ASTVisitor &visitor) override;
};

class FuncFParamList {
public:
  vector<unique_ptr<FuncFParamNode>> list;
};

class FuncFParamNode : public BaseNode {
public:
  BType bType;
  unique_ptr<string> id;
  bool isArray = false;
  vector<unique_ptr<AddExpNode>> arrays;
  void accept(ASTVisitor &visitor) override;
};

class BlockNode : public BaseNode {
public:
  vector<unique_ptr<BlockItemNode>> blockItemList;
  void accept(ASTVisitor &visitor) override;
};

class BlockItemList {
public:
  vector<unique_ptr<BlockItemNode>> list;
};

class BlockItemNode : public BaseNode {
public:
  unique_ptr<DeclNode> decl = nullptr;
  unique_ptr<StmtNode> stmt = nullptr;
  void accept(ASTVisitor &visitor) override;
};

class StmtNode : public BaseNode {
public:
  StmtType sType;
  unique_ptr<LValNode> lVal = nullptr;
  unique_ptr<AddExpNode> exp = nullptr;
  unique_ptr<ReturnStmtNode> returnStmt = nullptr;
  unique_ptr<IfStmtNode> ifStmt = nullptr;
  unique_ptr<WhileStmtNode> whileStmtAST = nullptr;
  unique_ptr<BlockNode> block = nullptr;
  void accept(ASTVisitor &visitor) override;
};

class ReturnStmtNode : public BaseNode {
public:
  unique_ptr<AddExpNode> exp = nullptr;
  void accept(ASTVisitor &visitor) override;
};

class IfStmtNode : public BaseNode {
public:
  unique_ptr<LOrExpNode> cond;
  unique_ptr<StmtNode> ifStmt, elseStmt;
  void accept(ASTVisitor &visitor) override;
};

class WhileStmtNode : public BaseNode {
public:
  unique_ptr<LOrExpNode> cond;
  unique_ptr<StmtNode> stmt;
  void accept(ASTVisitor &visitor) override;
};

class UnaryExpNode : public BaseNode {
public:
  unique_ptr<PrimaryExpNode> primaryExp;
  unique_ptr<CallNode> call;
  unique_ptr<UnaryExpNode> unaryExp;
  UnaryOp op;
  void accept(ASTVisitor &visitor) override;
};

class AddExpNode : public BaseNode {
public:
  unique_ptr<AddExpNode> addExp;
  unique_ptr<MulExpNode> mulExp;
  AddOp op;
  void accept(ASTVisitor &visitor) override;
};

class MulExpNode : public BaseNode {
public:
  unique_ptr<UnaryExpNode> unaryExp;
  unique_ptr<MulExpNode> mulExp;
  MulOp op;
  void accept(ASTVisitor &visitor) override;
};

class NumberNode : public BaseNode {
public:
  bool isInt;
  union {
    int intval;
    float floatval;
  };

  void accept(ASTVisitor &visitor) override;
};

class PrimaryExpNode : public BaseNode {
public:
  unique_ptr<AddExpNode> exp;
  unique_ptr<LValNode> lval;
  unique_ptr<NumberNode> number;
  void accept(ASTVisitor &visitor) override;
};

class LValNode : public BaseNode {
public:
  unique_ptr<string> id;
  vector<unique_ptr<AddExpNode>> arrays;
  void accept(ASTVisitor &visitor) override;
};

class CallNode : public BaseNode {
public:
  unique_ptr<string> id;
  vector<unique_ptr<AddExpNode>> funcCParamList;
  void accept(ASTVisitor &visitor) override;
};

class FuncCParamList {
public:
  vector<unique_ptr<AddExpNode>> list;
};

class RelExpNode : public BaseNode {
public:
  unique_ptr<AddExpNode> addExp;
  unique_ptr<RelExpNode> relExp;
  RelOp op;
  void accept(ASTVisitor &visitor) override;
};

class EqExpNode : public BaseNode {
public:
  unique_ptr<RelExpNode> relExp;
  unique_ptr<EqExpNode> eqExp;
  EqOp op;
  void accept(ASTVisitor &visitor) override;
};

class LAndExpNode : public BaseNode {
public:
  unique_ptr<EqExpNode> eqExp;
  unique_ptr<LAndExpNode> lAndExp;
  void accept(ASTVisitor &visitor) override;
};

class LOrExpNode : public BaseNode {
public:
  unique_ptr<LOrExpNode> lOrExp;
  unique_ptr<LAndExpNode> lAndExp;
  void accept(ASTVisitor &visitor) override;
};

class ASTVisitor {
public:
  virtual void visit(CompUnitNode &ast) = 0;

  virtual void visit(DeclNode &ast) = 0;

  virtual void visit(DefNode &ast) = 0;

  virtual void visit(InitValNode &ast) = 0;

  virtual void visit(FuncDefNode &ast) = 0;

  virtual void visit(FuncFParamNode &ast) = 0;

  virtual void visit(BlockNode &ast) = 0;

  virtual void visit(BlockItemNode &ast) = 0;

  virtual void visit(StmtNode &ast) = 0;

  virtual void visit(ReturnStmtNode &ast) = 0;

  virtual void visit(IfStmtNode &ast) = 0;

  virtual void visit(WhileStmtNode &ast) = 0;

  virtual void visit(AddExpNode &ast) = 0;

  virtual void visit(MulExpNode &ast) = 0;

  virtual void visit(UnaryExpNode &ast) = 0;

  virtual void visit(PrimaryExpNode &ast) = 0;

  virtual void visit(LValNode &ast) = 0;

  virtual void visit(NumberNode &ast) = 0;

  virtual void visit(CallNode &ast) = 0;

  virtual void visit(RelExpNode &ast) = 0;

  virtual void visit(EqExpNode &ast) = 0;

  virtual void visit(LAndExpNode &ast) = 0;

  virtual void visit(LOrExpNode &ast) = 0;
};

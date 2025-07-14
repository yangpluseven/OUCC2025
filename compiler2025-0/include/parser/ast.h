#pragma once

#include "parser/define.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class BaseNode;

class CompUnit;
class DeclDef;
class Decl;
class DefList;
class Def;
class ArrayList;
class InitValList;
class InitVal;
class FuncDef;
class FuncFParamList;
class FuncFParam;
class Block;
class BlockItemList;
class BlockItem;
class Stmt;
class ReturnStmt;
class IfStmt;
class WhileStmt;
class LVal;
class PrimaryExp;
class Number;
class UnaryExp;
class Call;
class FuncCParamList;
class MulExp;
class AddExp;
class RelExp;
class EqExp;
class LAndExp;
class LOrExp;

class ASTVisitor;

// 结点基类
class BaseNode {
public:
  virtual void accept(ASTVisitor &visitor) = 0;
  BaseNode() = default;
  virtual ~BaseNode() = default;
};

class CompUnit : public BaseNode {
public:
  vector<unique_ptr<DeclDef>> declDefList; // declaration-definition-list
  void accept(ASTVisitor &visitor) override;
  ~CompUnit() {}
};

// 变量声明或函数定义
class DeclDef : public BaseNode {
public:
  unique_ptr<Decl> decl = nullptr;       // 声明结点
  unique_ptr<FuncDef> funcDef = nullptr; // 函数定义结点
  void accept(ASTVisitor &visitor) override;
  ~DeclDef() {}
};

// 变量声明
class Decl : public BaseNode {
public:
  Type bType = Type::VOID;         // 基本数据类型
  bool isConst = false;            // 是否为const声明
  vector<unique_ptr<Def>> defList; // 定义列表
  void accept(ASTVisitor &visitor) override;
  ~Decl() {}
};

// 定义列表
class DefList {
public:
  vector<unique_ptr<Def>> list;
};

// 定义
class Def : public BaseNode {
public:
  unique_ptr<string> id;             // 标识符
  vector<unique_ptr<AddExp>> arrays; // 数组下标列表
  unique_ptr<InitVal> initVal;       // 初始化值
  void accept(ASTVisitor &visitor) override;
  ~Def() {}
};

// 数组下标列表
class ArrayList {
public:
  vector<unique_ptr<AddExp>> list;
};

// 初始化值
class InitVal : public BaseNode {
public:
  unique_ptr<AddExp> exp; // 如果是单个表达式，则存储在exp中
  vector<unique_ptr<InitVal>>
      initValList; // 如果是初始化值列表，则存储在initValList中
  void accept(ASTVisitor &visitor) override;
  ~InitVal() {}
};

// 初始化值列表
class InitValList {
public:
  vector<unique_ptr<InitVal>> list;
};

// 函数定义
class FuncDef : public BaseNode {
public:
  Type returnType = Type::VOID;                  // 函数返回类型
  unique_ptr<string> id;                         // 函数名
  vector<unique_ptr<FuncFParam>> funcFParamList; // 函数形参列表
  unique_ptr<Block> block = nullptr;             // 函数体
  void accept(ASTVisitor &visitor) override;
  ~FuncDef() {}
};

// 函数形参列表
class FuncFParamList {
public:
  vector<unique_ptr<FuncFParam>> list;
};

// 函数形参
class FuncFParam : public BaseNode {
public:
  Type bType;
  unique_ptr<string> id; // 标识符
  bool isArray =
      false; // 用于区分是否是数组参数，此时一维数组和多维数组expArrays都是empty
  vector<unique_ptr<AddExp>> arrays; // 数组下标列表
  void accept(ASTVisitor &visitor) override;
  ~FuncFParam() {}
};

// 块
class Block : public BaseNode {
public:
  vector<unique_ptr<BlockItem>> blockItemList; // 语句块项列表
  void accept(ASTVisitor &visitor) override;
  ~Block() {}
};

// 语句块项列表
class BlockItemList {
public:
  vector<unique_ptr<BlockItem>> list;
};

// 语句块项
class BlockItem : public BaseNode {
public:
  unique_ptr<Decl> decl = nullptr; // 声明结点
  unique_ptr<Stmt> stmt = nullptr; // 语句结点
  void accept(ASTVisitor &visitor) override;
  ~BlockItem() {}
};

// 语句结
class Stmt : public BaseNode {
public:
  StmtType sType;
  unique_ptr<LVal> lVal = nullptr;              // 左值表达式结点
  unique_ptr<AddExp> exp = nullptr;             // 表达式结点
  unique_ptr<ReturnStmt> returnStmt = nullptr;  // return语句结点
  unique_ptr<IfStmt> ifStmt = nullptr;          // 条件语句结点
  unique_ptr<WhileStmt> whileStmtAST = nullptr; // 循环语句结点
  unique_ptr<Block> block = nullptr;            // 代码块结点
  void accept(ASTVisitor &visitor) override;
  ~Stmt() {}
};

// return语句
class ReturnStmt : public BaseNode {
public:
  unique_ptr<AddExp> exp = nullptr; // 返回值表达式结点
  void accept(ASTVisitor &visitor) override;
  ~ReturnStmt() {}
};

// 条件语句
class IfStmt : public BaseNode {
public:
  unique_ptr<LOrExp> cond;           // 条件表达式结点
  unique_ptr<Stmt> ifStmt, elseStmt; // if语句和else语句结点
  void accept(ASTVisitor &visitor) override;
  ~IfStmt() {}
};

// 循环语句
class WhileStmt : public BaseNode {
public:
  unique_ptr<LOrExp> cond; // 条件表达式结点
  unique_ptr<Stmt> stmt;   // 循环体语句结点
  void accept(ASTVisitor &visitor) override;
  ~WhileStmt() {}
};

// 一元表达式
class UnaryExp : public BaseNode {
public:
  unique_ptr<PrimaryExp> primaryExp; // 基本表达式结点
  unique_ptr<Call> call;             // 函数调用结点
  unique_ptr<UnaryExp> unaryExp;     // 一元表达式结点（递归）
  UnaryOp op;                        // 一元操作符
  void accept(ASTVisitor &visitor) override;
  ~UnaryExp() {}
};

// 加减表达式
class AddExp : public BaseNode {
public:
  unique_ptr<AddExp> addExp; // 加减表达式结点（递归）
  unique_ptr<MulExp> mulExp; // 乘除模表达式结点
  AddOp op;                  // 加减操作符
  void accept(ASTVisitor &visitor) override;
  ~AddExp() {}
};

// 乘除模表达式
class MulExp : public BaseNode {
public:
  unique_ptr<UnaryExp> unaryExp; // 一元表达式结点
  unique_ptr<MulExp> mulExp;     // 乘除模表达式结点（递归）
  MulOp op;                      // 乘除模操作符
  void accept(ASTVisitor &visitor) override;
  ~MulExp() {}
};

// 基本表达式
class PrimaryExp : public BaseNode {
public:
  unique_ptr<AddExp> exp;    // 表达式结点
  unique_ptr<LVal> lval;     // 左值表达式结点
  unique_ptr<Number> number; // 数字结点
  void accept(ASTVisitor &visitor) override;
  ~PrimaryExp() {}
};

// 数字
class Number : public BaseNode {
public:
  bool isInt; // 是否为整型
  union {
    int intval;     // 整型值
    float floatval; // 浮点型值
  };
  void accept(ASTVisitor &visitor) override;
  ~Number() {}
};

// 左值表达式
class LVal : public BaseNode {
public:
  unique_ptr<string> id;             // 标识符
  vector<unique_ptr<AddExp>> arrays; // 数组下标列表
  void accept(ASTVisitor &visitor) override;
  ~LVal() {}
};

// 函数调用
class Call : public BaseNode {
public:
  unique_ptr<string> id;                     // 函数名
  vector<unique_ptr<AddExp>> funcCParamList; // 函数实参列表
  void accept(ASTVisitor &visitor) override;
  ~Call() {}
};

// 函数实参列表
class FuncCParamList {
public:
  vector<unique_ptr<AddExp>> list;
};

// 关系表达式
class RelExp : public BaseNode {
public:
  unique_ptr<AddExp> addExp; // 加减表达式结点
  unique_ptr<RelExp> relExp; // 关系表达式结点（递归）
  RelOp op;                  // 关系操作符
  void accept(ASTVisitor &visitor) override;
  ~RelExp() {}
};

// 等值表达式
class EqExp : public BaseNode {
public:
  unique_ptr<RelExp> relExp; // 关系表达式结点
  unique_ptr<EqExp> eqExp;   // 等值表达式结点（递归）
  EqOp op;                   // 等值操作符
  void accept(ASTVisitor &visitor) override;
  ~EqExp() {}
};

// 逻辑与表达式
class LAndExp : public BaseNode {
public:
  // lAndExp不为空则说明有and符号，or类似
  unique_ptr<EqExp> eqExp;     // 等值表达式结点
  unique_ptr<LAndExp> lAndExp; // 逻辑与表达式结点（递归）
  void accept(ASTVisitor &visitor) override;
  ~LAndExp() {}
};

// 逻辑或表达式
class LOrExp : public BaseNode {
public:
  unique_ptr<LOrExp> lOrExp;   // 逻辑或表达式结点（递归）
  unique_ptr<LAndExp> lAndExp; // 逻辑与表达式结点
  void accept(ASTVisitor &visitor) override;
  ~LOrExp() {}
};

class ASTVisitor {
public:
  virtual void visit(CompUnit &ast) = 0;
  virtual void visit(DeclDef &ast) = 0;
  virtual void visit(Decl &ast) = 0;
  virtual void visit(Def &ast) = 0;
  virtual void visit(InitVal &ast) = 0;
  virtual void visit(FuncDef &ast) = 0;
  virtual void visit(FuncFParam &ast) = 0;
  virtual void visit(Block &ast) = 0;
  virtual void visit(BlockItem &ast) = 0;
  virtual void visit(Stmt &ast) = 0;
  virtual void visit(ReturnStmt &ast) = 0;
  virtual void visit(IfStmt &ast) = 0;
  virtual void visit(WhileStmt &ast) = 0;
  virtual void visit(AddExp &ast) = 0;
  virtual void visit(MulExp &ast) = 0;
  virtual void visit(UnaryExp &ast) = 0;
  virtual void visit(PrimaryExp &ast) = 0;
  virtual void visit(LVal &ast) = 0;
  virtual void visit(Number &ast) = 0;
  virtual void visit(Call &ast) = 0;
  virtual void visit(RelExp &ast) = 0;
  virtual void visit(EqExp &ast) = 0;
  virtual void visit(LAndExp &ast) = 0;
  virtual void visit(LOrExp &ast) = 0;
};

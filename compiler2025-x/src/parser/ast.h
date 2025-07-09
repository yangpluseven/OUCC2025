#pragma once

#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "define.h"

using namespace std;
class BaseAST;

class CompUnitAST;
class DeclDefAST;
class DeclAST;
class DefListAST;
class DefAST;
class ArraysAST;
class InitValListAST;
class InitValAST;
class FuncDefAST;
class FuncFParamListAST;
class FuncFParamAST;
class BlockAST;
class BlockItemListAST;
class BlockItemAST;
class StmtAST;
class ReturnStmtAST;
class SelectStmtAST;
class IterationStmtAST;
class LValAST;
class PrimaryExpAST;
class NumberAST;
class UnaryExpAST;
class CallAST;
class FuncCParamListAST;
class MulExpAST;
class AddExpAST;
class RelExpAST;
class EqExpAST;
class LAndExpAST;
class LOrExpAST;

class Visitor;

// AST结点基类
class BaseAST {
public:
    virtual void accept(Visitor &visitor) = 0;
    BaseAST() = default;
    virtual ~BaseAST() = default;
};

// 编译单元结点
class CompUnitAST : public BaseAST {
public:
    vector<unique_ptr<DeclDefAST>> declDefList; // 声明或定义列表（declaration-definition-list）
    void accept(Visitor &visitor) override;
};

// 变量声明或函数定义结点
class DeclDefAST : public BaseAST {
public:
    unique_ptr<DeclAST> Decl = nullptr; // 声明结点
    unique_ptr<FuncDefAST> funcDef = nullptr; // 函数定义结点
    void accept(Visitor &visitor) override;
};

// 变量声明结点
class DeclAST : public BaseAST {
public:
    TYPE bType = TYPE_VOID; // 基本数据类型
    bool isConst = false; // 是否为const声明
    vector<unique_ptr<DefAST>> defList; // 定义列表
    void accept(Visitor &visitor) override;
};

// 辅助结构：定义列表
class DefListAST {
public:
    vector<unique_ptr<DefAST>> list;
};

// 定义结点
class DefAST : public BaseAST {
public:
    unique_ptr<string> id; // 标识符
    vector<unique_ptr<AddExpAST>> arrays; // 数组下标列表
    unique_ptr<InitValAST> initVal; // 初始化值
    void accept(Visitor &visitor) override;
};

// 辅助结构：数组下标列表
class ArraysAST {
public:
    vector<unique_ptr<AddExpAST>> list;
};

// 初始化值结点
class InitValAST : public BaseAST {
public:
    unique_ptr<AddExpAST> exp; // 如果是单个表达式，则存储在exp中
    vector<unique_ptr<InitValAST>> initValList; // 如果是初始化值列表，则存储在initValList中
    void accept(Visitor &visitor) override;
};

// 辅助结构：初始化值列表
class InitValListAST {
public:
    vector<unique_ptr<InitValAST>> list;
};

// 函数定义结点
class FuncDefAST : public BaseAST {
public:
    TYPE funcType = TYPE_VOID; // 函数返回类型
    unique_ptr<string> id; // 函数名
    vector<unique_ptr<FuncFParamAST>> funcFParamList; // 函数形参列表
    unique_ptr<BlockAST> block = nullptr; // 函数体
    void accept(Visitor &visitor) override;
};

// 辅助结构：函数形参列表
class FuncFParamListAST {
public:
    vector<unique_ptr<FuncFParamAST>> list;
};

// 函数形参结点
class FuncFParamAST : public BaseAST {
public:
    TYPE bType;
    unique_ptr<string> id; // 标识符
    bool isArray = false; // 用于区分是否是数组参数，此时一维数组和多维数组expArrays都是empty
    vector<unique_ptr<AddExpAST>> arrays; // 数组下标列表
    void accept(Visitor &visitor) override;
};

// 语句块结点
class BlockAST : public BaseAST {
public:
    vector<unique_ptr<BlockItemAST>> blockItemList; // 语句块项列表
    void accept(Visitor &visitor) override;
};

// 辅助结构：语句块项列表
class BlockItemListAST {
public:
    vector<unique_ptr<BlockItemAST>> list;
};

// 语句块项结点
class BlockItemAST : public BaseAST {
public:
    unique_ptr<DeclAST> decl = nullptr; // 声明结点
    unique_ptr<StmtAST> stmt = nullptr; // 语句结点
    void accept(Visitor &visitor) override;
};

// 语句结点
class StmtAST : public BaseAST {
public:
    STYPE sType;
    unique_ptr<LValAST> lVal = nullptr; // 左值表达式结点
    unique_ptr<AddExpAST> exp = nullptr; // 表达式结点
    unique_ptr<ReturnStmtAST> returnStmt = nullptr; // return语句结点
    unique_ptr<SelectStmtAST> selectStmt = nullptr; // 条件语句结点
    unique_ptr<IterationStmtAST> iterationStmt = nullptr; // 循环语句结点
    unique_ptr<BlockAST> block = nullptr; // 代码块结点
    void accept(Visitor &visitor) override;
};

// return语句结点
class ReturnStmtAST : public BaseAST {
public:
    unique_ptr<AddExpAST> exp = nullptr; // 返回值表达式结点
    void accept(Visitor &visitor) override;
};

// 条件语句结点
class SelectStmtAST : public BaseAST {
public:
    unique_ptr<LOrExpAST> cond; // 条件表达式结点
    unique_ptr<StmtAST> ifStmt, elseStmt; // if语句和else语句结点
    void accept(Visitor &visitor) override;
};

// 循环语句结点
class IterationStmtAST : public BaseAST {
public:
    unique_ptr<LOrExpAST> cond; // 条件表达式结点
    unique_ptr<StmtAST> stmt; // 循环体语句结点
    void accept(Visitor &visitor) override;
};

// 加减表达式结点
class AddExpAST : public BaseAST {
public:
    unique_ptr<AddExpAST> addExp; // 加减表达式结点（递归）
    unique_ptr<MulExpAST> mulExp; // 乘除模表达式结点
    AOP op; // 加减操作符
    void accept(Visitor &visitor) override;
};

// 乘除模表达式结点
class MulExpAST : public BaseAST {
public:
    unique_ptr<UnaryExpAST> unaryExp; // 一元表达式结点
    unique_ptr<MulExpAST> mulExp; // 乘除模表达式结点（递归）
    MOP op; // 乘除模操作符
    void accept(Visitor &visitor) override;
};

// 一元表达式结点
class UnaryExpAST : public BaseAST {
public:
    unique_ptr<PrimaryExpAST> primaryExp; // 基本表达式结点
    unique_ptr<CallAST> call; // 函数调用结点
    unique_ptr<UnaryExpAST> unaryExp; // 一元表达式结点（递归）
    UOP op; // 一元操作符
    void accept(Visitor &visitor) override;
};

// 基本表达式结点
class PrimaryExpAST : public BaseAST {
public:
    unique_ptr<AddExpAST> exp; // 表达式结点
    unique_ptr<LValAST> lval; // 左值表达式结点
    unique_ptr<NumberAST> number; // 数字结点
    void accept(Visitor &visitor) override;
};

// 数字结点
class NumberAST : public BaseAST {
public:
    bool isInt; // 是否为整型
    union {
        int intval; // 整型值
        float floatval; // 浮点型值
    };
    void accept(Visitor &visitor) override;
};

// 左值表达式结点
class LValAST : public BaseAST {
public:
    unique_ptr<string> id; // 标识符
    vector<unique_ptr<AddExpAST>> arrays; // 数组下标列表
    void accept(Visitor &visitor) override;
};

// 函数调用结点
class CallAST : public BaseAST {
public:
    unique_ptr<string> id; // 函数名
    vector<unique_ptr<AddExpAST>> funcCParamList; // 函数实参列表
    void accept(Visitor &visitor) override;
};

// 辅助结构：函数实参列表
class FuncCParamListAST {
public:
    vector<unique_ptr<AddExpAST>> list;
};

// 关系表达式结点
class RelExpAST : public BaseAST {
public:
    unique_ptr<AddExpAST> addExp; // 加减表达式结点
    unique_ptr<RelExpAST> relExp; // 关系表达式结点（递归）
    ROP op; // 关系操作符
    void accept(Visitor &visitor) override;
};

// 等值表达式结点
class EqExpAST : public BaseAST {
public:
    unique_ptr<RelExpAST> relExp; // 关系表达式结点
    unique_ptr<EqExpAST> eqExp; // 等值表达式结点（递归）
    EOP op; // 等值操作符
    void accept(Visitor &visitor) override;
};

// 逻辑与表达式结点
class LAndExpAST : public BaseAST {
public:
    // lAndExp不为空则说明有and符号，or类似
    unique_ptr<EqExpAST> eqExp; // 等值表达式结点
    unique_ptr<LAndExpAST> lAndExp; // 逻辑与表达式结点（递归）
    void accept(Visitor &visitor) override;
};

// 逻辑或表达式结点
class LOrExpAST : public BaseAST {
public:
    unique_ptr<LOrExpAST> lOrExp; // 逻辑或表达式结点（递归）
    unique_ptr<LAndExpAST> lAndExp; // 逻辑与表达式结点
    void accept(Visitor &visitor) override;
};

class Visitor {
public:
    virtual void visit(CompUnitAST &ast) = 0;
    virtual void visit(DeclDefAST &ast) = 0;
    virtual void visit(DeclAST &ast) = 0;
    virtual void visit(DefAST &ast) = 0;
    virtual void visit(InitValAST &ast) = 0;
    virtual void visit(FuncDefAST &ast) = 0;
    virtual void visit(FuncFParamAST &ast) = 0;
    virtual void visit(BlockAST &ast) = 0;
    virtual void visit(BlockItemAST &ast) = 0;
    virtual void visit(StmtAST &ast) = 0;
    virtual void visit(ReturnStmtAST &ast) = 0;
    virtual void visit(SelectStmtAST &ast) = 0;
    virtual void visit(IterationStmtAST &ast) = 0;
    virtual void visit(AddExpAST &ast) = 0;
    virtual void visit(MulExpAST &ast) = 0;
    virtual void visit(UnaryExpAST &ast) = 0;
    virtual void visit(PrimaryExpAST &ast) = 0;
    virtual void visit(LValAST &ast) = 0;
    virtual void visit(NumberAST &ast) = 0;
    virtual void visit(CallAST &ast) = 0;
    virtual void visit(RelExpAST &ast) = 0;
    virtual void visit(EqExpAST &ast) = 0;
    virtual void visit(LAndExpAST &ast) = 0;
    virtual void visit(LOrExpAST &ast) = 0;
};

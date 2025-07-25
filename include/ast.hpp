//
// Created by 22673 on 25-7-24.
//

#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <string>
#include <memory>
#include <variant>
#include <optional>

#include "define.hpp"


namespace Compiler
{
class BaseNode
{
public:
    virtual ~BaseNode() = default;
};

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
class NumberNode;
class UnaryExp;
class Call;
class FuncCParamList;
class MulExp;
class AddExp;
class RelExp;
class EqExp;
class LAndExp;
class LOrExp;

class CompUnit final : public BaseNode
{
public:
    std::vector<std::unique_ptr<DeclDef> > declDefList;
};

class DeclDef final : public BaseNode
{
public:
    std::unique_ptr<Decl> decl;
    std::unique_ptr<FuncDef> funcDef;
};

class Decl final : public BaseNode
{
public:
    bool isConst;
    Type bType;
    std::vector<std::unique_ptr<Decl> > declList;
};

class DefList final : public BaseNode
{
public:
    std::vector<std::unique_ptr<Def> > defList;
};

class Def final : public BaseNode
{
public:
    std::unique_ptr<std::string> id;
    std::vector<std::unique_ptr<AddExp> > arrays;
    std::unique_ptr<InitVal> initVal;
};

class ArrayList final : public BaseNode
{
public:
    std::vector<std::unique_ptr<AddExp> > list;
};

class InitValList final : public BaseNode
{
public:
    std::vector<std::unique_ptr<InitVal> > list;
};

class InitVal final : public BaseNode
{
public:
    std::unique_ptr<AddExp> exp;
    std::vector<std::unique_ptr<InitVal> > initValList;

    bool is_list_init() const;
};

class FuncDef final : public BaseNode
{
public:
    Type returnType;
    std::unique_ptr<std::string> id;
    std::vector<std::unique_ptr<FuncFParam> > funcFParamList;
    std::unique_ptr<Block> block;
};

class FuncFParamList final : public BaseNode
{
public:
    std::vector<std::unique_ptr<FuncFParam> > list;
};

class FuncFParam final : public BaseNode
{
public:
    Type bType;
    std::unique_ptr<std::string> id;
    bool isArray;
    std::vector<std::unique_ptr<AddExp> > arrays;
};

class Block final : public BaseNode
{
public:
    std::vector<std::unique_ptr<BlockItem> > blockItemList;
};

class BlockItemList final : BaseNode
{
public:
    std::vector<std::unique_ptr<BlockItem> > list;
};

class BlockItem final : public BaseNode
{
public:
    std::unique_ptr<Decl> decl;
    std::unique_ptr<Stmt> stmt;
};

class Stmt final : public BaseNode
{
public:
    StmtType sType;
    std::unique_ptr<LVal> lVal;
    std::unique_ptr<AddExp> exp;
    std::unique_ptr<Block> block;
    std::unique_ptr<ReturnStmt> returnStmt;
    std::unique_ptr<IfStmt> ifStmt;
    std::unique_ptr<WhileStmt> whileStmt;
};

class ReturnStmt final : public BaseNode
{
public:
    std::unique_ptr<AddExp> exp;
};

class IfStmt final : public BaseNode
{
public:
    std::unique_ptr<LOrExp> cond;
    std::unique_ptr<Stmt> ifStmt, elseStmt;
};

class WhileStmt final : public BaseNode
{
    std::unique_ptr<LOrExp> cond;
    std::unique_ptr<Stmt> stmt;
};

class LVal final : public BaseNode
{
public:
    std::unique_ptr<std::string> id;
    std::vector<std::unique_ptr<AddExp> > arrays;
};

class PrimaryExp final : public BaseNode
{
public:
    std::unique_ptr<AddExp> exp;
    std::unique_ptr<LVal> lVal;
    std::unique_ptr<NumberNode> number;
};

class NumberNode final : public BaseNode
{
public:
    Type bType;

    union
    {
        int intValue;
        float floatValue;
    };
};

class UnaryExp final : public BaseNode
{
public:
    std::unique_ptr<PrimaryExp> primaryExp;
    std::unique_ptr<Call> call;

    struct
    {
        UnaryOp op;
        std::unique_ptr<UnaryExp> unaryExp;
    } opExp;

    bool has_op() const;
};

class Call final : public BaseNode
{
public:
    std::unique_ptr<std::string> id;
    std::vector<std::unique_ptr<AddExp> > funcCParamList;
};

class FuncCParamList final : public BaseNode
{
public:
    std::vector<std::unique_ptr<AddExp> > list;
};

class MulExp final : public BaseNode
{
public:
    std::unique_ptr<UnaryExp> unaryExp;
    std::unique_ptr<MulExp> mulExp;
    std::optional<MulOp> op;

};

class AddExp final : public BaseNode
{
public:
    std::unique_ptr<MulExp> mulExp;
    std::unique_ptr<AddExp> addExp;
    std::optional<AddOp> op;
};

class RelExp final : public BaseNode
{
public:
    std::unique_ptr<AddExp> addExp;
    std::unique_ptr<RelExp> relExp;
    std::optional<RelOp> op;
};

class EqExp final : public BaseNode
{
public:
    std::unique_ptr<RelExp> relExp;
    std::unique_ptr<EqExp> eqExp;
    std::optional<EqOp> op;
};

class LAndExp final : public BaseNode
{
    std::unique_ptr<EqExp> eqExp;
    std::unique_ptr<LAndExp> lAndExp;
};

class LOrExp final : public BaseNode
{
    std::unique_ptr<LAndExp> lAndExp;
    std::unique_ptr<LOrExp> lOrExp;
};
};


#endif //AST_HPP
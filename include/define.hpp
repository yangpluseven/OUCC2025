//
// Created by 22673 on 25-7-24.
//

#ifndef DEFINE_HPP
#define DEFINE_HPP

namespace Compiler
{
enum class Type
{
    INT, FLOAT, VOID
};

enum class StmtType
{
    SEMI, ASGN, EXP, CONTINUE, BREAK, RET, BLK, IF, WHILE
};

enum class UnaryOp
{
    ADD, MINUS, NOT
};

enum class AddOp
{
    ADD, MINUS
};

enum class MulOp
{
    MUL, DIV, MOD
};

enum class RelOp
{
    GTE, LTE, GT, LT
};

enum class EqOp
{
    EQ, NEQ
};
}

#endif //DEFINE_HPP
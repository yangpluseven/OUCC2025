#pragma once

// 语句类型：分号、赋值、表达式、continue、break、return、代码块、选择语句、循环语句
enum STYPE { SEMI, ASS, EXP, CONT, BRE, RET, BLK, SEL, ITER };

// 单目运算符：加法、减法
enum UOP { UOP_ADD, UOP_MINUS, UOP_NOT };

// 加减运算符：加法、减法
enum AOP { AOP_ADD, AOP_MINUS };

// 乘除模运算符：乘法、除法、取模
enum MOP { MOP_MUL, MOP_DIV, MOP_MOD };

// 关系操作符：大于等于、小于等于、大于、小于
enum ROP { ROP_GTE, ROP_LTE, ROP_GT, ROP_LT };

// 关系操作符：等于、不等于
enum EOP { EOP_EQ, EOP_NEQ };

// 数据类型：void、int、float
enum TYPE { TYPE_VOID, TYPE_INT, TYPE_FLOAT };

#ifndef BASICOPERATION
#define BASICOPERATION
#include "ir.h"
//这个基本函数用来在 suc（后继块）中找到所有 phi 指令，把来自 bb（某前驱块）的对应输入项去掉  
//简化phi甚至消除phi
void SolvePhi(BasicBlock *bb, BasicBlock *succ_bb);
void DeleteUnusedBB(Function *func);
void dfsGraph(BasicBlock *bb, std::set<BasicBlock *> &vis);

#endif // !BASICOPERATION
#ifndef __LT_TREE_H__
#define __LT_TREE_H__

#include "opt.h"

// 这个文件是用来生成支配树的
class LengauerTarjan: public Optimization {
public:
    LengauerTarjan(Module* m): Optimization(m) {}
    void execute() {
        for (auto *f : m->function_list_) {
            //std::cout << f->name_ << std::endl;
            if (!f->basic_blocks_.empty()) {
                build_dominator_tree(f);
                // for (auto bb : f->basic_blocks_) {
                //     std::cout << "bb: " << bb->name_ 
                //               << ", idom_: " << (bb->idom_ ? bb->idom_->name_ : "null") 
                //               << std::endl;
                // }
                compute_dom_frontier(f);
                // for(auto bb : f->basic_blocks_) {
                //     std::cout << bb->name_ << " ";
                //     if(bb->idom_) std::cout << bb->idom_->name_ << std::endl;
                // }
                build_reverse_dom_tree(f);
                build_reverse_dom_frontier(f);
            }
        }
    }

private:
    std::map<BasicBlock*, int> dfs_num; // 深度优先访问基本块的顺序
    std::vector<BasicBlock* > vertex; // 深度优先访问的基本块列表
    std::map<BasicBlock*, BasicBlock*> parent; // 深度优先访问下基本块的父结点
    std::map<BasicBlock*, BasicBlock*> semi; // 半支配者
    std::map<BasicBlock*, BasicBlock*> idom;
    std::map<BasicBlock*, std::vector<BasicBlock*>> bucket;
    std::map<BasicBlock*, BasicBlock*> ancestor;
    std::map<BasicBlock*, BasicBlock*> label;
    std::map<BasicBlock *, std::vector<BasicBlock *>> reverseDomTree;

    void build_dominator_tree(Function* f);
    void compute_dom_frontier(Function* f);
    void build_reverse_dom_tree(Function* func);
    void build_reverse_dom_frontier(Function* func);

    void dfs(BasicBlock* v, int& N); // 初始化支配树所需要的数据结构
    void compress(BasicBlock* v); // 路径压缩
    BasicBlock* eval(BasicBlock* v); // 求取最优半支配者
    void link(BasicBlock* v, BasicBlock* w); // 连接基本块，建立父子关系
};

#endif // __LT_TREE_H__
#include "BasicOperation.h"
#include <vector>

void SolvePhi(BasicBlock *bb, BasicBlock *succ_bb){
    std::vector<Instruction*> useless_phi;
    for(auto instr: succ_bb->instr_list_){
        if(instr->is_phi()){
            //phi操作数中，奇数是bb 偶数是val
            for(int i = 1;i < instr->num_ops_;i++){
                if(instr->get_operand(i) == bb ){
                    instr->remove_operands(i - 1, i);
                    break;
                }
            }
            if (instr->parent_->pre_bbs_.size() == 1) {
                Value *only = instr->get_operand(0);
                instr->replace_all_use_with(only);
                useless_phi.push_back(instr);
            }
        }
    }
    for(auto instr : useless_phi)
        succ_bb->delete_instr(instr);
}

//用于遍历CFG控制流图，登记有边到达的basicblock
void dfsGraph(BasicBlock *bb, std::set<BasicBlock *> &vis) {
    if (!bb)
      return;
    vis.insert(bb);
    for (auto suc : bb->succ_bbs_) {
      if (vis.find(suc) == vis.end())
        dfsGraph(suc, vis);
    }
  }

//删除到达不了的无用basicblock
void DeleteUnusedBB(Function* func){
    std::set<BasicBlock *> vis;
    for (auto bb : func->basic_blocks_)
      if (bb->name_ == "label_entry") {
        dfsGraph(bb, vis);
        break;
    }
    for (auto bb : func->basic_blocks_)
      if (vis.find(bb) == vis.end()) {
        bb->parent_->remove_bb(bb);
        for (auto suc : bb->succ_bbs_)
          SolvePhi(bb, suc);
    }
}
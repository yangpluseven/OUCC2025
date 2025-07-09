#ifndef __MEM2REG_H__
#define __MEM2REG_H__

#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "ir.h"
#include "opt.h"

struct AllocaInfo;
class LargeBlockInfo;
struct RenamePassData;

class Mem2Reg : public Optimization {
public:
    explicit Mem2Reg(Module* m) : Optimization(m) {}
    void execute() override {
        for (auto *f : m->function_list_) {
            if (!f->basic_blocks_.empty()) {
                insert_phi(f);
            }
        }
    }

private:
    void insert_phi(Function* func);
    bool is_promotable(AllocaInst* alloca);
    void removeLifetimeIntrinsicUsers(AllocaInst* AI);
    bool rewriteSingleStoreAlloca(AllocaInst* AI, AllocaInfo &Info, LargeBlockInfo &LBI);
    bool promoteSingleBlockAlloca(AllocaInst* AI, AllocaInfo &Info, LargeBlockInfo &LBI);
    bool QueuePhiNode(BasicBlock* BB, unsigned AllocaNum, unsigned &Version);
    void RenamePass(BasicBlock* bb, BasicBlock* pred, std::vector<Value*>& incomingVals,
                    std::vector<RenamePassData>& workList, std::unordered_set<Instruction*>& delInstr);
    void compute_live_in_blocks(AllocaInst* AI, AllocaInfo &Info, std::set<BasicBlock*> &def_blocks, std::set<BasicBlock*> &live_in_blocks);
    
    void RemoveFromAllocasList(unsigned &AllocaIdx) {
        promotable_allocas[AllocaIdx] = promotable_allocas.back();
        promotable_allocas.pop_back();
        --AllocaIdx;
    }

    std::map<std::pair<unsigned, unsigned>, PhiInst*> new_phi_nodes_;  // <block_id, alloca_id> → phi
    std::vector<AllocaInst*> promotable_allocas;
    unsigned num_phi_insert_ = 0;
    std::map<PhiInst* , unsigned> phi_to_alloca_map_;
    std::unordered_map<AllocaInst*, int> allocaLookup;
    std::unordered_set<BasicBlock*> visited;
};

//用于收集信息
struct AllocaInfo {
    std::vector<BasicBlock*> DefBlocks;
    std::vector<BasicBlock*> UseBlocks;
  
    StoreInst* OnlyStore = nullptr;
    BasicBlock* OnlyBlock = nullptr;
    bool UsedInOneBlock = true;
  
    void analyze(AllocaInst* AI) {
        clear();
    
        for (auto &use : AI->use_list_) {
            auto inst = dynamic_cast<Instruction*>(use.val_);
            if (!inst) continue;
            auto bb = inst->parent_;
            
            
            //store指令是定义
            if (auto store = dynamic_cast<StoreInst*>(inst)) {
                DefBlocks.push_back(bb);
                //std::cout << bb->name_ << std::endl;
                OnlyStore = store;
            } else {       //load指令是使用
                UseBlocks.push_back(bb);
            }
            
            // 是否都在同一个块中？
            if(UsedInOneBlock){
                if (!OnlyBlock)
                    OnlyBlock = bb;
                else if (OnlyBlock != bb)
                    UsedInOneBlock = false;
            }
        }
    }
  
    void clear() {
        DefBlocks.clear();
        UseBlocks.clear();
        OnlyStore = nullptr;
        OnlyBlock = nullptr;
        UsedInOneBlock = true;
    }
};

class LargeBlockInfo {
public:
    // 判断是否是对 alloca 的 load/store 指令
    static bool is_interesting(Instruction* inst) {
        if (inst->is_load()) {
            auto ptr = inst->get_operand(0);
            return dynamic_cast<AllocaInst*>(ptr) != nullptr;
        }
        if (inst->is_store()) {
            auto ptr = inst->get_operand(1);
            return dynamic_cast<AllocaInst*>(ptr) != nullptr;
        }
        return false;
    }
    // 获取某条指令在 basic block 中的顺序编号
    unsigned get_instruction_index(Instruction* inst) {
        assert(is_interesting(inst) && "not a load/store to alloca");

        if (inst_index_map_.count(inst))
            return inst_index_map_.at(inst);

        BasicBlock* bb = inst->parent_;
        unsigned idx = 0;
        for (auto cur_inst : bb->instr_list_) {
            if (is_interesting(cur_inst)) {
                inst_index_map_[cur_inst] = idx++;
            }
        }
        assert(inst_index_map_.count(inst) && "instruction not indexed?");
        return inst_index_map_.at(inst);
    }
    // 删除某条已记录指令
    void delete_value(Instruction* inst) { inst_index_map_.erase(inst); }
    // 清空所有记录
    void clear() { inst_index_map_.clear(); }

private:
    // 记录某条指令在所属 BasicBlock 中的顺序编号
    std::unordered_map<Instruction*, unsigned> inst_index_map_;
};

class IDFCalculator {
public:
    // 构造函数传入 dominator tree 根（可选）
    IDFCalculator() = default;
    // 设置定义块集合（store发生的地方）
    void set_defining_blocks(const std::set<BasicBlock*> &defs) {
        def_blocks_ = defs;
    }
    // 设置活跃入口块集合（变量活跃使用）
    void set_live_in_blocks(const std::set<BasicBlock*> &live_ins) {
        live_in_blocks_ = live_ins;
    }

    void calculate(std::vector<BasicBlock*> &phi_blocks) {
        std::queue<BasicBlock*> worklist;
        std::unordered_set<BasicBlock*> has_phi;        // 记录哪些块已插入phi
        std::unordered_set<BasicBlock*> defsites(def_blocks_.begin(), def_blocks_.end());
    
        for (auto bb : def_blocks_) worklist.push(bb);
    
        while (!worklist.empty()) {
            BasicBlock* bb = worklist.front();
            worklist.pop();

            // std::cout << "dom_frontier of " << bb->name_ << ": ";
            // for (auto df : bb->dom_frontier_) {
            //     std::cout << df->name_ << " ";
            // }
            // std::cout << std::endl << std::endl;
    
            for (BasicBlock* df : bb->dom_frontier_) {
                // 只在活跃块里插phi
                if (!live_in_blocks_.count(df))
                    continue;
    
                if (!has_phi.count(df)) {
                    phi_blocks.push_back(df);
                    has_phi.insert(df);
    
                    // phi相当于新的defsite
                    if (!defsites.count(df)) {
                        defsites.insert(df);
                        worklist.push(df); // 递归处理DF
                    }
                }
            }
        }
    }
    

private:
    std::set<BasicBlock*> def_blocks_;
    std::set<BasicBlock*> live_in_blocks_;
};


struct RenamePassData {
    BasicBlock* bb;
    BasicBlock* pred;
    std::vector<Value*> vals;

    RenamePassData(BasicBlock* bb_, BasicBlock* pred_, std::vector<Value*> val_) :bb(bb_), pred(pred_), vals((val_)) {} // 删除了std::move
};

class PostOrderDFS {
    public:
        std::unordered_map<BasicBlock*, int> post_order;
        std::unordered_set<BasicBlock*> visited;
        int counter;
    
        void run(BasicBlock* entry) {
            counter = 0;
            dfs(entry);
        }
    
    private:
        void dfs(BasicBlock* bb) {
            visited.insert(bb);
            for (auto* succ : bb->succ_bbs_) {
                if (visited.count(succ) == 0) {
                    dfs(succ);
                }
            }
            post_order[bb] = counter++;
        }
    };







#endif // __MEM2REG_H__
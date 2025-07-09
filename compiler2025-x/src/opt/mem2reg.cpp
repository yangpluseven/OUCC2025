#include "mem2reg.h"
#include <fstream>
bool Mem2Reg::is_promotable(AllocaInst* alloca) {
    //std::cout << alloca->print() << std::endl;
    for (auto use : alloca->use_list_) {
        auto user = use.val_;
        auto inst = dynamic_cast<Instruction*>(user);
        if (!inst) {
            return false;
        }
        if (inst->is_load()) {
            // ok
        } else if (inst->is_store()) {
            // store 的第二个操作数必须是 alloca 本身  不允许把alloca放入别的变量中
            if (inst->get_operand(1) != alloca)
                return false;
        } else {
            // 出现其他用法，如 bitcast, getelementptr 等，都不能提升
            // 这里和官方的有区别，官方对bitcast在lifetime.*是可以接受的
            // 但是代码中目前好像没有这个东西，所以先一律false处理
            return false;
        }
    }
    return true;
}

//这里其实有点冗余目前 补过先写着
void Mem2Reg::removeLifetimeIntrinsicUsers(AllocaInst* AI) {
    std::vector<Instruction*> to_remove;

    // 收集所有不合法的 use
    for (auto& use : AI->use_list_) {
        auto user = dynamic_cast<Instruction*>(use.val_);
        if (user && !user->is_load() && !user->is_store()) {
            to_remove.push_back(user);
        }
    }

    // 逐个删除（先 remove_use，再从 parent 删除）
    for (auto inst : to_remove) {
        inst->remove_use_of_ops();                // 清掉所有 operands 的 use 链
        if (inst->parent_) {
            inst->parent_->delete_instr(inst);    // 从 basicblock 中删除指令
        }
        delete inst; // 如果你没有垃圾回收机制
    }
}

bool Mem2Reg::rewriteSingleStoreAlloca(AllocaInst* AI, AllocaInfo &Info, LargeBlockInfo &LBI){
    StoreInst* store = Info.OnlyStore;
    Value* ReplVal = store->get_operand(0); // 获取 store 的值  用于后续的替换
    int store_index = -1;  //用于存储store的位置

    BasicBlock* store_bb = store->parent_;

    std::vector<LoadInst*> to_delete;

    Info.UseBlocks.clear(); // 清除之前的使用块信息

    for (auto& use : AI->use_list_) {
        auto user = dynamic_cast<Instruction*>(use.val_);
        if (!user) continue;

        if (user == store) continue;

        //处理load
        if (auto load = dynamic_cast<LoadInst*>(user)) {
            auto load_bb = load->parent_;

            // 在同一个块中，且 load 在 store 之后（可通过顺序判断）
            //这个官网中是增加了一个class Largeblock来辅助
            //使用largeblock可以查询一次就记录下来，不需要每次都重新遍历一遍
            //后面可以进行优化 先暂时用最朴素的方法，每次都查找一下
            if (load_bb == store_bb) {
                if(store_index == -1) {
                    // 找到 store 在 store_bb 中的位置
                    store_index = LBI.get_instruction_index(store);
                }
                if(unsigned(store_index) > LBI.get_instruction_index(load)){
                    Info.UseBlocks.push_back(load_bb);
                    continue;
                }
            }
            else {
                // 不在同一块，检查支配关系
                if (!load_bb->is_dominated_by(store_bb)) {
                    Info.UseBlocks.push_back(load_bb);
                    continue;
                }
            }

            // 替换这个 load
            load->replace_all_use_with(ReplVal);
            to_delete.push_back(load);
        }
    }

    for (auto ld : to_delete) {
        ld->parent_->delete_instr(ld);
    }

    if (!Info.UseBlocks.empty()) return false;

    store_bb->delete_instr(store);

    auto entry_block_ = AI->parent_->parent_->basic_blocks_.front();
    entry_block_->delete_instr(AI);

    return true;

}

bool Mem2Reg::promoteSingleBlockAlloca(AllocaInst* AI, AllocaInfo &Info,
                                       LargeBlockInfo &LBI) {
    using StoresByIndexTy = std::vector<std::pair<unsigned, StoreInst*>>;
    StoresByIndexTy StoresByIndex;

    //收集store指令并按照顺序进行排序
    for (auto use : AI->use_list_) {
        auto inst = dynamic_cast<StoreInst*>(use.val_);
        if (inst)
            StoresByIndex.emplace_back(LBI.get_instruction_index(inst), inst);
    }

    std::sort(StoresByIndex.begin(), StoresByIndex.end());

    //去找load指令
    std::vector<std::list<Use>::iterator> to_erase;
    for (auto it = AI->use_list_.begin(); it != AI->use_list_.end(); ++it) {
        auto load = dynamic_cast<LoadInst*>(it->val_);
        if (!load) {
            continue;
        }

        unsigned LoadIdx = LBI.get_instruction_index(load);

        auto lower = std::lower_bound(
            StoresByIndex.begin(), StoresByIndex.end(),
            std::make_pair(LoadIdx, (StoreInst* )nullptr),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        Value* repl_val = nullptr;
        if (lower == StoresByIndex.begin()) {
            if (StoresByIndex.empty()) {
                return false; 
            } else {
                return true;
            }
        } else {
            repl_val = std::prev(lower)->second->get_operand(0);
        }

        // 替换 load 的所有使用
        load->replace_all_use_with(repl_val);
        // 删除该指令（释放 load）
        load->parent_->delete_instr(load);
        // 延迟删除对应的 use_list_ 节点
        to_erase.push_back(it);
    }
    // 最后统一擦除
    for (auto it : to_erase) {
        AI->use_list_.erase(it);
    }

    //删除所有store 已经没用了
    for (auto it = AI->use_list_.begin(); it != AI->use_list_.end();) {
        auto store = dynamic_cast<StoreInst*>(it->val_);
        if (store) {
            store->parent_->delete_instr(store);
            it = AI->use_list_.erase(it);
        } else {
            ++it;
        }
    }

    // 删除该alloca
    AI->parent_->delete_instr(AI);
    return true;

}

void Mem2Reg::compute_live_in_blocks(AllocaInst* AI, AllocaInfo &Info,
                                      std::set<BasicBlock*> &def_blocks,
                                      std::set<BasicBlock*> &live_in_blocks){
                                        
    std::vector<BasicBlock*> worklist(Info.UseBlocks.begin(), Info.UseBlocks.end());                                      
    for(unsigned i = 0, e = worklist.size(); i != e; ++i){
        BasicBlock* bb = worklist[i];
        if(!def_blocks.count(bb)) {
            continue;
        }
        //这个块既use又def了value
        //如果def在use前面，则要将这个块去掉
        for(Instruction* inst : bb->instr_list_) {
            if(inst->is_store()){
                if(inst->get_operand(1) != AI) 
                    continue;
                worklist[i] = worklist.back();
                worklist.pop_back();
                --i;
                --e;
                break;                
            }

            if(inst->is_load()){
                if(inst->get_operand(0) != AI) 
                    continue;
                break;
            }

        }
    }

    // Now that we have a set of blocks where the phi is live-in, recursively add
    // their predecessors until we find the full region the value is live.
    while(!worklist.empty()) {
        //从最后一个开始
        BasicBlock* bb = worklist.back();
        worklist.pop_back();

        // 如果已经存在，跳过
        if(!live_in_blocks.insert(bb).second) 
            continue;

        for(BasicBlock* pred : bb->pre_bbs_){
            if(def_blocks.count(pred)) 
                continue;
            worklist.push_back(pred);
        }

    }

}

bool Mem2Reg::QueuePhiNode(BasicBlock* BB, unsigned AllocaNum, unsigned &Version){
    std::pair<unsigned, unsigned> key = {BB->dom_level_, AllocaNum};
    // std::cout << BB->name_ << std::endl;
    // std::cout << BB->dom_level_ << " " << AllocaNum << std::endl;
    // std::cout << std::endl;
    //这里错了，挂掉了一个block导致错误
    if(new_phi_nodes_.count(key))
        return false;
     
    
    auto alloca = promotable_allocas[AllocaNum];
    Type* type = static_cast<PointerType*>(alloca->type_)->contained_;

    std::string phi_name = alloca->name_ + "." + std::to_string(Version++);
    PhiInst* phi = PhiInst::create_phi(type, BB);

    BB->add_instruction_front(phi);
    phi->name_ = phi_name;

    new_phi_nodes_[key] = phi;
    ++num_phi_insert_;
    phi_to_alloca_map_[phi] = AllocaNum;
    return true;

}

void Mem2Reg::RenamePass(BasicBlock* bb, BasicBlock* pred,
    std::vector<Value*>& incomingVals,
    std::vector<RenamePassData>& workList,
    std::unordered_set<Instruction*>& delInstr){
    
    std::unordered_set<BasicBlock*> visitedSuccs;

    while (true) {
        // === Step 1: Insert PHI incoming values ===
        if (pred != nullptr && dynamic_cast<PhiInst*>(bb->instr_list_.front())) {
            for (auto instr : bb->instr_list_) {
                auto phi = dynamic_cast<PhiInst*>(instr);
                if (!phi) {
                    break;
                }
                int allocId = phi_to_alloca_map_.at(phi);
                bool found = false;
                for (int i = 1; i < phi->operands_.size(); i += 2) {
                    if (phi->operands_[i] == pred) {
                        phi->replace_operand(i - 1, incomingVals[allocId]);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    phi->add_phi_pair_operand(incomingVals[allocId], pred);
                }
                incomingVals[allocId] = phi;
            }
        }

        // === Step 2: Skip visited blocks ===
        if (!visited.insert(bb).second) {
            return;
        }
        // === Step 3: Rewrite loads and stores ===
        for (auto instr : bb->instr_list_) {
            if (delInstr.count(instr)) continue;

            if (auto load = dynamic_cast<LoadInst*>(instr)) {
                auto src = dynamic_cast<AllocaInst*>(load->get_operand(0));
                if (!src || allocaLookup.count(src) == 0) continue;

                Value* val = incomingVals[allocaLookup[src]];
                load->replace_all_use_with(val);
                delInstr.insert(load);

            } else if (auto store = dynamic_cast<StoreInst*>(instr)) {
                auto dest = dynamic_cast<AllocaInst*>(store->get_operand(1));
                if (!dest || allocaLookup.count(dest) == 0) {
                    continue;
                }
                incomingVals[allocaLookup[dest]] = store->get_operand(0);
                delInstr.insert(store);
            }
        }

        // === Step 4: Add successors to worklist ===
        if (bb->succ_bbs_.empty()) {
            return;
        }
        BasicBlock* origin = bb;
        auto succIt = origin->succ_bbs_.begin();
        BasicBlock* firstSucc =* succIt++;

        visitedSuccs.insert(firstSucc);
        pred = bb;
        bb = firstSucc;

        for (; succIt != origin->succ_bbs_.end(); ++succIt) {
            if (visitedSuccs.insert(*succIt).second) {
                workList.emplace_back(*succIt, pred, incomingVals);
            }
        }
    }
}
void Mem2Reg::insert_phi(Function* func) {
    new_phi_nodes_.clear();
    //std::cout << func->print() << std::endl;
    func->set_instr_name();
    //第一步 收集所有可提升的变量
    //假设：所有可提升变量都在entry block中定义   -> 需要与前端配合检查  后续
    auto entry_bb = func->basic_blocks_.front();


    PostOrderDFS podfs;
    podfs.run(entry_bb);
    
    unsigned level_id = 0 ;
    for (auto& [bb, order] : podfs.post_order) {
        bb->dom_level_ = level_id++;
        //std::cout << bb->name_ << " post_order = " << order << "\n";
    }

    for (auto& inst : entry_bb->instr_list_)
        if (auto alloca = dynamic_cast<AllocaInst*>(inst)) 
            if(is_promotable(alloca))  // 如果是可提升的变量，加入 promotable_allocas
                promotable_allocas.push_back(alloca);
    
    // for (auto alloca : promotable_allocas) {
    //     // 可以在这里对每个可提升的alloca做一些操作
    //     // 例如输出信息或做额外分析
    //     std::cout << "Promotable alloca: " << alloca->name_ << std::endl;
    // }
        
    if(promotable_allocas.empty()) {
        return; // 没有可提升的变量，直接返回
    }

    //第二步 遍历每个可提升变量
    AllocaInfo Info;
    LargeBlockInfo LBI;
    IDFCalculator IDF;

    for (unsigned AllocaNum = 0  ;  AllocaNum != promotable_allocas.size(); ++AllocaNum){
        unsigned CurrentVersion = 0;
        AllocaInst* AI = promotable_allocas[AllocaNum];
        //if(func->name_ == "main") std::cout << AI->print() << std::endl;
        //删除涉及该变量所有非load / store指令
        //removeLifetimeIntrinsicUsers(AI);
        if(AI->use_list_.empty()) {
            // 如果没有使用，直接删除
            AI->parent_->delete_instr(AI);
            RemoveFromAllocasList(AllocaNum);
            continue;
        }
        //收集该变量的使用信息 完成数据流结构分析
        Info.analyze(AI);

        // //当只有一个def时，直接把这个值替代所有对应的 load 指令 不需要phi或者变量重命名
        if (Info.DefBlocks.size() == 1) {
            //std::cout << AI->name_ << std::endl;
            // TODO 下面这个函数暂时存在问题，有时候会不出phi函数  
            if (rewriteSingleStoreAlloca(AI, Info, LBI)) {
                // The alloca has been processed, move on.
                RemoveFromAllocasList(AllocaNum);
                continue;
            }
        }


        // TODO 代码存在问题
        // //如果use和def都在一个块中，使用线性扫描来消除
        // if (Info.UsedInOneBlock &&
        //     promoteSingleBlockAlloca(AI, Info, LBI)) {
        //   // The alloca has been processed, move on.
        //   RemoveFromAllocasList(AllocaNum);
        //   continue;
        // }

        allocaLookup[promotable_allocas[AllocaNum]] = AllocaNum;

        // Unique the set of defining blocks for efficient lookup.
        std::set<BasicBlock*> def_blocks(Info.DefBlocks.begin(), Info.DefBlocks.end());
        std::set<BasicBlock*> live_in_blocks;
        compute_live_in_blocks(AI, Info, def_blocks, live_in_blocks);
        
        IDF.set_defining_blocks(def_blocks);
        IDF.set_live_in_blocks(live_in_blocks);
        std::vector<BasicBlock*> phi_blocks;
        IDF.calculate(phi_blocks);


        if(phi_blocks.size() > 1){
            std::sort(phi_blocks.begin(), phi_blocks.end(), [](BasicBlock* A, BasicBlock* B) {
                return A->dom_level_ > B->dom_level_;
            });
        }

        for (BasicBlock* BB : phi_blocks)
            QueuePhiNode(BB, AllocaNum, CurrentVersion);
    }
    
    if(promotable_allocas.empty())
        return ;
    
    LBI.clear();
    
    //开始rename
    std::vector<Value*> values(promotable_allocas.size());
    for (int i = 0; i < promotable_allocas.size(); i++){
		Type* ty = dynamic_cast<PointerType*>(promotable_allocas[i]->type_)->contained_;
		assert(dynamic_cast<PointerType*>(promotable_allocas[i]->type_)->contained_ = promotable_allocas[i]->alloca_ty_);
		values[i] = new ValUndef(ty, "undef");
	}

    std::unordered_set<Instruction*> delInstr;
    std::vector<RenamePassData> RenamePassWorkList;
    RenamePassWorkList.emplace_back(func->basic_blocks_.front(), nullptr, std::move(values));

    do { // TODO 存在死循环 未知是否解决
        RenamePassData RPD = std::move(RenamePassWorkList.back());
        RenamePassWorkList.pop_back();
        RenamePass(RPD.bb, RPD.pred, RPD.vals, RenamePassWorkList, delInstr);
    } while (!RenamePassWorkList.empty());
    visited.clear();

    for(auto alloc: promotable_allocas) {
        delInstr.insert(alloc);
    }
    for (auto alloc: promotable_allocas) {
        for(auto use:alloc->use_list_) {
            auto user = use.val_;
            delInstr.insert(dynamic_cast<Instruction*>(user));
        }
    }
    for(auto inst: delInstr){
        auto parent = inst->parent_;
        assert(parent);
        parent->delete_instr(inst);
    }
}
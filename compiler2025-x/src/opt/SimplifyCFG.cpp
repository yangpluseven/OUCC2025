#include "SimplifyCFG.h"
#include <cassert>


bool checkUselessJump(BasicBlock* bb)
{
	// 假定已经检验 bb->instr_list_.size() == 1 and Typeid = unconditionalBranch
	bool isOk = false;

	Value* jumpPos = bb->instr_list_.front()->operands_[0];

	for (auto pre : bb->pre_bbs_)
	{
		// 获取 pre 的跳转指令
		auto preBr = pre->get_terminator();
		// 判断是否为有条件跳转指令
		if (preBr->is_br() && preBr->operands_.size() == 3)
		{
			Value* jumpPosa = preBr->operands_[1], * jumpPosb = preBr->operands_[2];
			if (jumpPosa == bb)
			{
				if (jumpPosb == jumpPos)
				{
					return false;
				}
			}
			else if (jumpPosb == bb)
			{
				if (jumpPosa == jumpPos)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool SimplifyUnconditionalBranch::simplifyUnconditionalBranchOnFunction2(Function* func)
{
	std::set<BasicBlock*> delBB;
	bool changed = false;

	for (auto bb : func->basic_blocks_)
	{
		if (bb->name_ == "label_entry" || bb->name_ == "label_ret") // 排除label_entry
		{
			continue;
		}
		if (delBB.find(bb) != delBB.end())
		{
			continue;
		}
		if (bb->instr_list_.size() == 1) // 仅仅包含一条语句
		{
			// 获取唯一的一条指令
			Instruction* onlyInstr = bb->instr_list_.front();
			// 需要满足唯一的一条指令为 无条件 指令
			if (onlyInstr->is_br() && onlyInstr->operands_.size() == 1 && checkUselessJump(bb))
			{
				// std::cout << "I comeIn" << std::endl;
				bool isOk = true;
				bool hasPhi = false;
				std::vector<int> phiArgNos;
				std::vector<PhiInst*> phis;
				for (auto use : bb->use_list_)
				{
					if (dynamic_cast<PhiInst*>(use.val_))
					{
						hasPhi = true;
						phis.push_back(dynamic_cast<PhiInst*>(use.val_));
						phiArgNos.push_back(use.arg_no_);
						if(!dynamic_cast<ConstantInt*>(phis.back()->operands_[use.arg_no_ - 1]) && !dynamic_cast<ConstantInt*>(phis.back()->operands_[use.arg_no_ - 1]))
						{
							isOk = false;
							// std::cout << "ssssssssssssssssssssssssssssssssss" << std::endl;
							break;
						}
					}
				}
				
				if(isOk == false)
					continue;

				// std::cout << "hasPhi = " << hasPhi << std::endl;
				if (hasPhi == false)
				{
					// 删除前驱后继关系
					BasicBlock* nextBB = static_cast<BasicBlock*>(onlyInstr->operands_[0]);
					nextBB->remove_pre_basic_block(bb);
					bb->remove_succ_basic_block(nextBB);


					// 将该基本块给剔除
					bb->delete_instr(bb->instr_list_.front());
					bb->replace_all_use_with(nextBB);

					// 建立新的前驱后继关系
					for (auto pre : bb->pre_bbs_)
					{
						pre->add_succ_basic_block(nextBB);
						nextBB->add_pre_basic_block(pre);
					}
					
					// [Terribly]:删除前驱后继关系
					for (auto pre : bb->pre_bbs_)
					{
						pre->remove_succ_basic_block(bb);
						bb->remove_pre_basic_block(pre);
					}


					delBB.insert(bb);
				}
				else
				{
					// std::cout << "phis.size() == " << phis.size() << std::endl;
					for (int i = 0; i < phis.size(); i++)
					{
						// std::cout << phiArgNos[i] << std::endl;
						int phiArgNo = phiArgNos[i];
						PhiInst* phi = phis[i];

						
						// 首先第一步：获取Value
						Value* ConstValue = phi->operands_[phiArgNo - 1];
						// assert(dynamic_cast<Instruction*>(ConstValue));
						// std::cout << "ConstValue->name == " << dynamic_cast<Instruction*>(ConstValue)->name_ << std::endl;
						assert(ConstValue->is_constant() && (dynamic_cast<ConstantInt*>(ConstValue) || dynamic_cast<ConstantFloat*>(ConstValue)));
						
						// std::cout << "pass assert" << std::endl;

						// 然后第二步：将这两个操作数删除
						phi->remove_operands(phiArgNo - 1, phiArgNo);

						// 最后第三步：添加这个关系
						for (auto pre : bb->pre_bbs_)
						{
							// std::cout << "pre->name = " << pre->name_ << std::endl;
							if (delBB.find(pre) != delBB.end())
								continue;
							// std::cout << "pass delBB" << std::endl;
							if (ConstValue->type_->tid_ == Type::IntegerTyID)
							{
								// std::cout << "what" << std::endl;
								// assert(dynamic_cast<GlobalVariable*>(ConstValue));
								auto newConst = new ConstantInt(ConstValue->type_, dynamic_cast<ConstantInt*>(ConstValue)->value_);
								// std::cout << "here and pre->name = " << pre->name_ << std::endl;
								phi->add_phi_pair_operand(newConst, pre);
							}
							else if (ConstValue->type_->tid_ == Type::FloatTyID)
							{
								auto newConst = new ConstantFloat(ConstValue->type_, dynamic_cast<ConstantFloat*>(ConstValue)->value_);
								// std::cout << "newConst" << std::endl;
								phi->add_phi_pair_operand(newConst, pre);
							}
						}
					}

					// 删除前驱后继关系
					BasicBlock* nextBB = static_cast<BasicBlock*>(onlyInstr->operands_[0]);
					nextBB->remove_pre_basic_block(bb);
					bb->remove_succ_basic_block(nextBB);


					// 将该基本块给剔除
					bb->delete_instr(bb->instr_list_.front());
					bb->replace_all_use_with(nextBB);

					// 建立新的前驱后继关系
					for (auto pre : bb->pre_bbs_)
					{
						pre->add_succ_basic_block(nextBB);
						nextBB->add_pre_basic_block(pre);
					}


					// [Terribly]：删除前驱后继关系应该放在这里
					for (auto pre : bb->pre_bbs_)
					{
						pre->remove_succ_basic_block(bb);
						bb->remove_pre_basic_block(pre);
					}

					delBB.insert(bb);
				}
				
				// std::cout << "I came Out" << std::endl;
			}
		}
	}

	for (auto delbb : delBB)
	{
		func->remove_bb(delbb);
	}

	changed = delBB.size() != 0;

	return changed;
}

bool SimplifyUnconditionalBranch::simplifyUnconditionalBranchOnFunction(Function* func)
{
	std::set<BasicBlock*> delBB;

	bool changed = false;

	//for(auto bb : func->basic_blocks_)
	//	std::cout << "bb->pre = " << bb->pre_bbs_.size() << std::endl;
	for (auto bb : func->basic_blocks_)
	{
		if (bb->name_ == "label_entry") // 排除label_entry
		{
			continue;
		}
		if (delBB.find(bb) != delBB.end())
		{
			continue;
		}


		if (bb->succ_bbs_.size() == 1) // 需要满足后继基本块的数量为1
		{
			// std::cout << "It ?? " << std::endl;
			auto succ_bb = bb->succ_bbs_[0]; // 获取后继基本块
			if (succ_bb->pre_bbs_.size() != 1 || delBB.find(succ_bb) != delBB.end() || succ_bb->name_ == "label_ret") // 需要满足后续基本块的前驱基本块的数量为1
			{
				// std::cout << "succ_bb->prebbs.size() = " << succ_bb->pre_bbs_.size() << std::endl;
				continue;
			}
			assert(bb == succ_bb->pre_bbs_[0]);

			// 标记changed = true
			changed = true;

			// 当前需要将bb同pre_bb进行合并
			auto preBr = bb->get_terminator();
			bb->delete_instr(preBr);
			// 【Terribly】移除前驱后继关系
			bb->remove_succ_basic_block(succ_bb);
			succ_bb->remove_pre_basic_block(bb);

			// std::cout << "here" << std::endl;
			// 将后续块中的指令添加至前驱块中
			for (auto it = succ_bb->instr_list_.begin(); it != succ_bb->instr_list_.end();)
			{
				// 后继块中的phiInstr需要特殊处理
				auto instr = *it;
				it++;
				if (it == succ_bb->instr_list_.end())
				{
					// std::cout << "the the" << std::endl;
					succ_bb->remove_instr(instr);
					bb->add_instruction(instr);
					break;
				}
				else
				{
					succ_bb->remove_instr(instr);
					bb->add_instruction(instr);
				}
			}

			// 修改前驱后继关系
			for (auto succ : succ_bb->succ_bbs_)
			{
				bb->add_succ_basic_block(succ);
				// std::cout << succ->pre_bbs_.size() << " =========================================================" << std::endl;
				succ->remove_pre_basic_block(succ_bb);
				// std::cout << succ->pre_bbs_.size() << " =========================================================" << std::endl;
				succ->add_pre_basic_block(bb);
				// std::cout << succ->pre_bbs_.size() << " =========================================================" << std::endl;
			}

			// 将所有的后续块的使用转换为对前驱块的引用
			succ_bb->replace_all_use_with(bb);

			// 将该基本块删除，暂时加入delBB
			delBB.insert(succ_bb);
		}
	}
	for (auto delbb : delBB)
	{
		func->remove_bb(delbb);
	}

	return changed;
}

void SimplifyUnconditionalBranch::deleteUselessPhi(Function* func)
{
	std::vector<Instruction*> delInstr;
	for (auto bb : func->basic_blocks_)
	{
		if (bb->pre_bbs_.size() == 1)
		{
			for (auto instr : bb->instr_list_)
			{
				if (instr->is_phi())
				{
					// 查找需要替换的值
					Value* val = nullptr;
					for (int i = 0; i < instr->operands_.size(); i += 2)
					{
						if (dynamic_cast<ValUndef*>(instr->operands_[i]))
							continue;

						if (dynamic_cast<BasicBlock*>(instr->operands_[i + 1]) != bb->pre_bbs_[0])
							continue;
						assert(dynamic_cast<BasicBlock*>(instr->operands_[i + 1]) == bb->pre_bbs_[0]);
						val = instr->operands_[i];
						break;
					}
					if (val != nullptr)
					{
						instr->replace_all_use_with(val);
						delInstr.push_back(instr);
					}
				}
			}
		}
	}
	for (auto instr : delInstr)
	{
		auto bb = instr->parent_;
		bb->delete_instr(instr);
	}
}

void SimplifyUnconditionalBranch::execute()
{
	for (auto func : m->function_list_)
	{
		if (func->basic_blocks_.empty())
			continue;
		deleteUselessPhi(func);
		while (simplifyUnconditionalBranchOnFunction(func));
		while (simplifyUnconditionalBranchOnFunction2(func));
	}
}








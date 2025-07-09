#include "ConstantFolding.h"


ConstantInt* ConstFolding::CalcInt(Instruction::OpID op, ConstantInt* v1, ConstantInt* v2)
{
    int a = v1->value_, b = v2->value_;
    switch (op) {
    case Instruction::Add:
        return new ConstantInt(m->int32_ty_, a + b);
    case Instruction::Sub:
        return new ConstantInt(m->int32_ty_, a - b);
    case Instruction::Mul:
        return new ConstantInt(m->int32_ty_, a * b);
    case Instruction::SDiv:
        return new ConstantInt(m->int32_ty_, a / b);
    case Instruction::SRem:
        return new ConstantInt(m->int32_ty_, a % b);
    case Instruction::Shl:
        return new ConstantInt(m->int32_ty_, a << b);
    case Instruction::LShr:
        return new ConstantInt(m->int32_ty_, (unsigned)a >> b);
    case Instruction::AShr:
        return new ConstantInt(m->int32_ty_, a >> b);
    case Instruction::And:
        return new ConstantInt(m->int32_ty_, a & b);
    case Instruction::Or:
        return new ConstantInt(m->int32_ty_, a | b);
    case Instruction::Xor:
        return new ConstantInt(m->int32_ty_, a ^ b);
    default:
        return nullptr;
    }
}

ConstantFloat* ConstFolding::CalcFloat(Instruction::OpID op, ConstantFloat* v1, ConstantFloat* v2){
    float a = v1->value_, b = v2->value_;
    switch (op) {
    case Instruction::FAdd:
        return new ConstantFloat(m->float32_ty_, a + b);
    case Instruction::FSub:
        return new ConstantFloat(m->float32_ty_, a - b);
    case Instruction::FMul:
        return new ConstantFloat(m->float32_ty_, a * b);
    case Instruction::FDiv:
        return new ConstantFloat(m->float32_ty_, a / b);
    default:
        return nullptr;
    }
}

ConstantInt* ConstFolding::CalcICMP(ICmpInst::ICmpOp op, ConstantInt* v1, ConstantInt* v2){
    int lhs = v1->value_;
    int rhs = v2->value_;
    switch (op) {
    case ICmpInst::ICMP_EQ:
        return new ConstantInt(m->int1_ty_, lhs == rhs);
    case ICmpInst::ICMP_NE:
        return new ConstantInt(m->int1_ty_, lhs != rhs);
    case ICmpInst::ICMP_SGT:
        return new ConstantInt(m->int1_ty_, lhs > rhs);
    case ICmpInst::ICMP_SGE:
        return new ConstantInt(m->int1_ty_, lhs >= rhs);
    case ICmpInst::ICMP_SLE:
        return new ConstantInt(m->int1_ty_, lhs <= rhs);
    case ICmpInst::ICMP_SLT:
        return new ConstantInt(m->int1_ty_, lhs < rhs);
    case ICmpInst::ICMP_UGE:
        return new ConstantInt(m->int1_ty_, (unsigned)lhs >= (unsigned)rhs);
    case ICmpInst::ICMP_ULE:
        return new ConstantInt(m->int1_ty_, (unsigned)lhs <= (unsigned)rhs);
    case ICmpInst::ICMP_ULT:
        return new ConstantInt(m->int1_ty_, (unsigned)lhs < (unsigned)rhs);
    case ICmpInst::ICMP_UGT:
        return new ConstantInt(m->int1_ty_, (unsigned)lhs > (unsigned)rhs);
    default:
        return nullptr;
    }
}

ConstantInt* ConstFolding::CalcFCMP(FCmpInst::FCmpOp op, ConstantFloat* v1, ConstantFloat* v2){
    float lhs = v1->value_;
    float rhs = v2->value_;
    switch (op) {
    case FCmpInst::FCMP_UEQ:
        return new ConstantInt(m->int1_ty_, lhs == rhs);
    case FCmpInst::FCMP_UNE:
        return new ConstantInt(m->int1_ty_, lhs != rhs);
    case FCmpInst::FCMP_UGT:
        return new ConstantInt(m->int1_ty_, lhs > rhs);
    case FCmpInst::FCMP_UGE:
        return new ConstantInt(m->int1_ty_, lhs >= rhs);
    case FCmpInst::FCMP_ULE:
        return new ConstantInt(m->int1_ty_, lhs <= rhs);
    case FCmpInst::FCMP_ULT:
        return new ConstantInt(m->int1_ty_, lhs < rhs);
    case FCmpInst::FCMP_FALSE:
        return new ConstantInt(m->int1_ty_, 0);
    case FCmpInst::FCMP_TRUE:
        return new ConstantInt(m->int1_ty_, 1);
    case FCmpInst::FCMP_OEQ:
        return new ConstantInt(m->int1_ty_, lhs == rhs);
    case FCmpInst::FCMP_ONE:
        return new ConstantInt(m->int1_ty_, lhs != rhs);
    case FCmpInst::FCMP_OGE:
        return new ConstantInt(m->int1_ty_, lhs >= rhs);
    case FCmpInst::FCMP_OGT:
        return new ConstantInt(m->int1_ty_, lhs > rhs);
    case FCmpInst::FCMP_OLE:
        return new ConstantInt(m->int1_ty_, lhs <= rhs);
    case FCmpInst::FCMP_OLT:
        return new ConstantInt(m->int1_ty_, lhs < rhs);
    default:
        return nullptr;
    }
}

//常量折叠之后，检查分支
bool ConstFolding::Deal_Branch(Function* func){
    bool tmp_change = false;
    for (auto bb : func->basic_blocks_)
    {   
        //分支语句只可能出现在基本块最后
        auto br = bb->get_terminator();
        if (!br) {
            continue;
        }

        // 条件分支语句
        if (br->op_id_ == Instruction::Br && dynamic_cast<BranchInst*>(br)->num_ops_ == 3)
        {
            //判断condition是不是常数
            auto cond = dynamic_cast<ConstantInt*>(br->get_operand(0));
            auto truebb = br->get_operand(1);
            auto falsebb = br->get_operand(2);
            if (cond == nullptr){
                continue;
            }
            tmp_change = true;
            // 分支的处理，对于总是false的分支
            if (cond->value_ == 0){
                bb->delete_instr(br);
                for (auto succ_bb : bb->succ_bbs_){
                    //对于不是falsebb目标的后继块，是不可能到达的
                    if (succ_bb != falsebb){
                        succ_bb->remove_pre_basic_block(bb);
                        SolvePhi(bb, succ_bb);
                    }
                }
                bb->succ_bbs_.clear();
                new BranchInst(dynamic_cast<BasicBlock*>(falsebb), bb);
            }
            else
            {
                bb->delete_instr(br);
                for (auto succ_bb : bb->succ_bbs_) {
                    if (succ_bb != truebb) {
                        succ_bb->remove_pre_basic_block(bb);
                        SolvePhi(bb, succ_bb);
                    }
                }
                bb->succ_bbs_.clear();
                new BranchInst(dynamic_cast<BasicBlock*>(truebb), bb);
            }
        }
    }
    return tmp_change;
}


bool ConstFolding::ConstantFolding_(Function* func){
    uselessInstr.clear();
    for(auto bb: func->basic_blocks_){
        for(auto instr: bb->instr_list_){
            ConstantInt* testConstInta = nullptr, * testConstIntb = nullptr;
            ConstantFloat* testConstFloata = nullptr, * testConstFloatb = nullptr;
            switch(instr->op_id_){
                //binary operation
                case Instruction::Add:
                case Instruction::Sub:
                case Instruction::Mul:
                case Instruction::SDiv:
                case Instruction::UDiv:
                case Instruction::SRem:
                case Instruction::URem:
                case Instruction::Shl:
                case Instruction::LShr:
                case Instruction::AShr:
                case Instruction::And:
                case Instruction::Or:
                case Instruction::Xor:{
                    //检测操作数是否为常量
                    testConstInta = dynamic_cast<ConstantInt*>(instr->get_operand(0)); // 检测是否为二元整型常数运算
                    testConstIntb = dynamic_cast<ConstantInt*>(instr->get_operand(1));

                    if (testConstInta && testConstIntb)
                    {
                        auto intRes = CalcInt(instr->op_id_, testConstInta, testConstIntb);
                        if (intRes)
                        {
                            instr->replace_all_use_with(intRes);
                            uselessInstr[instr] = bb;
                        }
                    }
                    break;
                }
                case Instruction::FAdd:
                case Instruction::FSub:
                case Instruction::FMul:
                case Instruction::FDiv:{
                    testConstFloata = dynamic_cast<ConstantFloat*>(instr->get_operand(0));
                    testConstFloatb = dynamic_cast<ConstantFloat*>(instr->get_operand(1));
                    if (testConstFloata && testConstFloatb)
                    {
                        auto floaRes = CalcFloat(instr->op_id_, testConstFloata, testConstFloatb);
                        if (floaRes)
                        {
                            instr->replace_all_use_with(floaRes);
                            uselessInstr[instr] = bb;
                        }
                    }
                    break;
                }
                case Instruction::ICmp:
                {
                    testConstInta = dynamic_cast<ConstantInt*>(instr->get_operand(0));
                    testConstIntb = dynamic_cast<ConstantInt*>(instr->get_operand(1));
                    if (testConstInta && testConstIntb)
                    {
                        auto boolRes = CalcICMP(dynamic_cast<ICmpInst*>(instr)->icmp_op_, testConstInta, testConstIntb);
                        if (boolRes) 
                        {
                            instr->replace_all_use_with(boolRes);
                            uselessInstr[instr] = bb;
                        }
                    }
                    break;
                }
                case Instruction::FCmp:
                {
                    testConstFloata = dynamic_cast<ConstantFloat*>(instr->get_operand(0));
                    testConstFloatb = dynamic_cast<ConstantFloat*>(instr->get_operand(1));
                    if (testConstFloata && testConstFloatb)
                    {
                        auto boolRes = CalcFCMP(dynamic_cast<FCmpInst*>(instr)->fcmp_op_, testConstFloata, testConstFloatb);
                        if (boolRes)
                        {
                            instr->replace_all_use_with(boolRes);
                            uselessInstr[instr] = bb;
                        }
                    }
                    break;
                }
                case Instruction::FNeg:
                {
                    testConstFloata = dynamic_cast<ConstantFloat*>(instr->get_operand(0));
                    if (testConstFloata)
                    {
                        instr->replace_all_use_with(new ConstantFloat(m->float32_ty_, -testConstFloata->value_));
                        uselessInstr[instr] = bb;
                    }
                    break;
                }
                case Instruction::FPtoSI:
            {
                testConstFloata = dynamic_cast<ConstantFloat*>(instr->get_operand(0));
                if (testConstFloata)
                {
                    instr->replace_all_use_with(new ConstantInt(m->int32_ty_, testConstFloata->value_));
                    uselessInstr[instr] = bb;
                }
                break;
            }
            case Instruction::SItoFP:
            {
                testConstInta = dynamic_cast<ConstantInt*>(instr->get_operand(0));
                if (testConstInta)
                {
                    instr->replace_all_use_with(new ConstantFloat(m->float32_ty_, testConstInta->value_));
                    uselessInstr[instr] = bb;
                }
                break;
            }
            case Instruction::ZExt:
            {
                testConstInta = dynamic_cast<ConstantInt*>(instr->get_operand(0));
                if (testConstInta)
                {
                    instr->replace_all_use_with(new ConstantInt(m->int32_ty_, testConstInta->value_));
                    uselessInstr[instr] = bb;
                }
                break;
            }
            case Instruction::Call:
            case Instruction::Load:
            case Instruction::Store:
            case Instruction::Alloca:
                break;
            default:
                break;
            
            }

        }
    }
    if (!uselessInstr.empty()){
        for (auto [instr, bb] : uselessInstr){
            bb->delete_instr(instr);
        }
        return true;
    }
    return false;
}


void ConstFolding::execute(){
    //对每个函数
    for(auto func: m->function_list_){
        if(func->basic_blocks_.empty())
            continue;
        bool change = true;
        while(change){
            change = false;
            change |= ConstantFolding_(func);
            change |= Deal_Branch(func);
            DeleteUnusedBB(func);
        }
    }
}
#ifndef CONSTANTFOLDINGH
#define CONSTANTFOLDINGH
#include "ir.h"
#include "opt.h"
#include "BasicOperation.h"

class ConstFolding : public Optimization
{
public:
	explicit ConstFolding(Module *m_) : Optimization(m_){}
	~ConstFolding(){}

	std::map<Instruction*, BasicBlock*> uselessInstr;

	ConstantInt* CalcInt(Instruction::OpID op, ConstantInt* v1, ConstantInt* v2);
	ConstantFloat* CalcFloat(Instruction::OpID op, ConstantFloat* v1, ConstantFloat* v2);

	ConstantInt* CalcICMP(ICmpInst::ICmpOp op, ConstantInt* v1, ConstantInt* v2);
	ConstantInt* CalcFCMP(FCmpInst::FCmpOp op, ConstantFloat* v1, ConstantFloat* v2);

	bool ConstantFolding_(Function* func);
	bool Deal_Branch(Function* func);

	void execute();
};
#endif // !CONSTANTFOLDINGH


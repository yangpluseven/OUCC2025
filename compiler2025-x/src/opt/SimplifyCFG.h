#ifndef SIMPLIFYUNCONDITIONALBRANCHH
#define SIMPLIFYUNCONDITIONALBRANCHH
#include "opt.h"


class SimplifyUnconditionalBranch : public Optimization
{
public:
	explicit SimplifyUnconditionalBranch(Module* m) :Optimization(m) {}
	~SimplifyUnconditionalBranch() {}


	void deleteUselessPhi(Function* func);
	bool simplifyUnconditionalBranchOnFunction(Function* func);
	bool simplifyUnconditionalBranchOnFunction2(Function* func);
	void execute();
	void executeBefore();
};

#endif // !SIMPLIFYUNCONDITIONALBRANCHH

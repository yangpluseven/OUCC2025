#ifndef __OPT_H__
#define __OPT_H__

#include "ir.h"
#include "BasicOperation.h"

class Optimization {
public:
    Module* m;
    explicit Optimization(Module *m_) : m(m_) {}
    virtual void execute() = 0;
};

#endif // __OPT_H__
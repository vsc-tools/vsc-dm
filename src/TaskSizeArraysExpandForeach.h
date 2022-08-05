
#pragma once
#include "vsc/IContext.h"
#include "vsc/impl/VisitorBase.h"
#include "SolveSet.h"

namespace vsc {

class TaskSizeArraysExpandForeach : public virtual VisitorBase {
public:

    TaskSizeArraysExpandForeach(IContext *ctxt);

    virtual ~TaskSizeArraysExpandForeach();

    void apply(SolveSet *sset);

private:
    IContext                    *m_ctxt;


};

}
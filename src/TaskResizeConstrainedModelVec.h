
#pragma once
#include <set>
#include <vector>
#include "vsc/IContext.h"
#include "vsc/ISolverFactory.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskResizeConstrainedModelVec : public VisitorBase {
public:
    TaskResizeConstrainedModelVec(
        IContext            *ctxt,
        ISolverFactory      *solver_f);

    virtual ~TaskResizeConstrainedModelVec();

    bool resize(SolveSet *solve_s);

	virtual void visitModelExprFieldRef(IModelExprFieldRef *f) override;

protected:
    IContext                            *m_ctxt;
    ISolverFactory                      *m_solver_f;
    std::set<IModelFieldVec *>          m_sizeref_vec_s;
    std::vector<IModelField *>          m_sizeref_vec_l;
    std::vector<IModelConstraintUP>     m_fixed_size_c;

};

}


#pragma once
#include "vsc/dm/IModelConstraintUnique.h"
#include "ModelConstraint.h"

namespace vsc {
namespace dm {

class ModelConstraintUnique : 
    public virtual IModelConstraintUnique,
    public virtual ModelConstraint {
public:

    ModelConstraintUnique(const std::vector<IModelExpr *> &exprs);

    virtual ~ModelConstraintUnique();

    virtual const std::vector<IModelExprUP> &getExprs() const override {
        return m_exprs;
    }

    virtual void accept(IVisitor *v) override { v->visitModelConstraintUnique(this); }

private:
    std::vector<IModelExprUP>           m_exprs;
};

}
}


#pragma once
#include "vsc/IModelConstraintUnique.h"

namespace vsc {

class ModelConstraintUnique : public virtual IModelConstraintUnique {
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
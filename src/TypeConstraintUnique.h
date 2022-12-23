
#pragma once
#include "vsc/dm/ITypeConstraintUnique.h"

namespace vsc {
namespace dm {

class TypeConstraintUnique : public virtual ITypeConstraintUnique {
public:

    TypeConstraintUnique(const std::vector<ITypeExpr *> &exprs);

    virtual ~TypeConstraintUnique();

    virtual const std::vector<ITypeExprUP> &getExprs() const override {
        return m_exprs;
    }

    virtual void accept(IVisitor *v) override { v->visitTypeConstraintUnique(this); }

private:
    std::vector<ITypeExprUP>            m_exprs;
};

}
}

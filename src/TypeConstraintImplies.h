
#pragma once
#include "vsc/ITypeConstraintImplies.h"

namespace vsc {

class TypeConstraintImplies : public virtual ITypeConstraintImplies {
public:
    TypeConstraintImplies(
        ITypeExpr       *cond,
        ITypeConstraint *body);

    virtual ~TypeConstraintImplies();

    virtual ITypeExpr *getCond() const override { return m_cond.get(); }

    virtual ITypeConstraint *getBody() const override { return m_body.get(); }

    virtual void accept(IVisitor *v) override { v->visitTypeConstraintImplies(this); }

private:
    ITypeExprUP         m_cond;
    ITypeConstraintUP   m_body;
};


}
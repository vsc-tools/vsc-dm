
#pragma once
#include "vsc/dm/ITypeConstraintImplies.h"

namespace vsc {
namespace dm {

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
}

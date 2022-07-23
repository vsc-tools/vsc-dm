
#pragma once
#include "vsc/ITypeConstraintSoft.h"

namespace vsc {

class TypeConstraintSoft : public virtual ITypeConstraintSoft {
public:

    TypeConstraintSoft(ITypeConstraintExpr *c);

    virtual ~TypeConstraintSoft();

    virtual ITypeConstraintExpr *constraint() const override {
        return m_constraint.get();
    }

    virtual void accept(IVisitor *v) override { v->visitTypeConstraintSoft(this); }

private:
    ITypeConstraintExprUP           m_constraint;

};

}

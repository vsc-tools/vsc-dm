
#pragma once
#include "vsc/dm/ITypeConstraintIfElse.h"

namespace vsc {
namespace dm {

class TypeConstraintIfElse : public virtual ITypeConstraintIfElse {
public:

    TypeConstraintIfElse(
        ITypeExpr           *cond,
        ITypeConstraint     *true_c,
        ITypeConstraint     *false_c
    );

    virtual ~TypeConstraintIfElse();

    virtual ITypeExpr *getCond() const override {
        return m_cond.get();
    }

    virtual ITypeConstraint *getTrue() const override {
        return m_true.get();
    }

    virtual ITypeConstraint *getFalse() const override {
        return m_false.get();
    }

    virtual void setFalse(ITypeConstraint *c) override {
        m_false = ITypeConstraintUP(c);
    }

    virtual void accept(IVisitor *v) override { v->visitTypeConstraintIfElse(this); }


private:
    ITypeExprUP             m_cond;
    ITypeConstraintUP       m_true;
    ITypeConstraintUP       m_false;

};

}
}



#pragma once
#include "vsc/ITypeExpr.h"
#include "vsc/ITypeConstraint.h"

namespace vsc {

class ITypeConstraintIfElse : public virtual ITypeConstraint {
public:
    virtual ~ITypeConstraintIfElse() { }

    virtual ITypeExpr *getCond() const = 0;

    virtual ITypeConstraint *getTrue() const = 0;

    virtual ITypeConstraint *getFalse() const = 0;

    virtual void setFalse(ITypeConstraint *c) = 0;

};

}
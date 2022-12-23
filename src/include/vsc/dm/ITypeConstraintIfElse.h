
#pragma once
#include "vsc/dm/ITypeExpr.h"
#include "vsc/dm/ITypeConstraint.h"

namespace vsc {
namespace dm {

class ITypeConstraintIfElse : public virtual ITypeConstraint {
public:
    virtual ~ITypeConstraintIfElse() { }

    virtual ITypeExpr *getCond() const = 0;

    virtual ITypeConstraint *getTrue() const = 0;

    virtual ITypeConstraint *getFalse() const = 0;

    virtual void setFalse(ITypeConstraint *c) = 0;

};

}
}

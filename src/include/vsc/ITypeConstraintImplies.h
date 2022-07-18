
#pragma once
#include "vsc/ITypeConstraint.h"
#include "vsc/ITypeExpr.h"

namespace vsc {
class ITypeConstraintImplies : public virtual ITypeConstraint {
public:

    virtual ~ITypeConstraintImplies() { }

    virtual ITypeExpr *getCond() const = 0;

    virtual ITypeConstraint *getBody() const = 0;

};

}
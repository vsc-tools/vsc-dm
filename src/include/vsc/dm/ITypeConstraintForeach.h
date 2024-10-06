
#pragma once
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/ITypeExpr.h"
#include "vsc/dm/ITypeVarScope.h"

namespace vsc {
namespace dm {

class ITypeConstraintForeach : 
    public virtual ITypeConstraint,
    public virtual ITypeVarScope {
public:

    virtual ~ITypeConstraintForeach() { }

    virtual ITypeExpr *getTarget() const = 0;

    virtual ITypeConstraint *getBody() const = 0;

};

}
}

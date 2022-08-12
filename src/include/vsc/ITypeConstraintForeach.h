
#pragma once
#include "vsc/ITypeConstraintScope.h"
#include "vsc/ITypeExpr.h"

namespace vsc {

class ITypeConstraintForeach : public virtual ITypeConstraintScope {
public:

    virtual ~ITypeConstraintForeach() { }

    virtual ITypeExpr *getTarget() const = 0;

};

}

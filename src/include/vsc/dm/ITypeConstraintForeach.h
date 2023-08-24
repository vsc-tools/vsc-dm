
#pragma once
#include "vsc/dm/ITypeConstraintScope.h"
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class ITypeConstraintForeach : public virtual ITypeConstraint {
public:

    virtual ~ITypeConstraintForeach() { }

    virtual ITypeExpr *getTarget() const = 0;

    virtual ITypeConstraint *getBody() const = 0;

};

}
}

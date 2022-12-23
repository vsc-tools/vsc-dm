
#pragma once
#include "vsc/dm/ITypeConstraintScope.h"
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class ITypeConstraintForeach : public virtual ITypeConstraintScope {
public:

    virtual ~ITypeConstraintForeach() { }

    virtual ITypeExpr *getTarget() const = 0;

};

}
}


#pragma once
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class ITypeConstraintImplies : public virtual ITypeConstraint {
public:

    virtual ~ITypeConstraintImplies() { }

    virtual ITypeExpr *getCond() const = 0;

    virtual ITypeConstraint *getBody() const = 0;

};

}
}

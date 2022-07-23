
#pragma once
#include "vsc/ITypeConstraintExpr.h"

namespace vsc {

class ITypeConstraintSoft : public virtual ITypeConstraint {
public:

    virtual ~ITypeConstraintSoft() { }

    virtual ITypeConstraintExpr *constraint() const = 0;

};


}
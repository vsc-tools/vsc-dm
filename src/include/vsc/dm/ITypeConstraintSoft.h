
#pragma once
#include "vsc/dm/ITypeConstraintExpr.h"

namespace vsc {
namespace dm {

class ITypeConstraintSoft : public virtual ITypeConstraint {
public:

    virtual ~ITypeConstraintSoft() { }

    virtual ITypeConstraintExpr *constraint() const = 0;

};

}
}

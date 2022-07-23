
#pragma once
#include <vector>
#include "vsc/ITypeConstraint.h"
#include "vsc/ITypeExpr.h"

namespace vsc {

class ITypeConstraintUnique : public virtual ITypeConstraint {
public:

    virtual ~ITypeConstraintUnique() { }

    virtual const std::vector<ITypeExprUP> &getExprs() const = 0;

};

}
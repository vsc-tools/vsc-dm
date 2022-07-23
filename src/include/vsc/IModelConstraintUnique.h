
#pragma once
#include <vector>
#include "vsc/IModelConstraint.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelConstraintUnique : public virtual IModelConstraint {
public:

    virtual ~IModelConstraintUnique() { }

    virtual const std::vector<IModelExprUP> &getExprs() const = 0;

};

}
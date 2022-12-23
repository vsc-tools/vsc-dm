
#pragma once
#include <vector>
#include "vsc/dm/IModelConstraint.h"
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelConstraintUnique : public virtual IModelConstraint {
public:

    virtual ~IModelConstraintUnique() { }

    virtual const std::vector<IModelExprUP> &getExprs() const = 0;

};

}
}

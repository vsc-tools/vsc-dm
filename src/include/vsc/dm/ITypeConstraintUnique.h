
#pragma once
#include <vector>
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class ITypeConstraintUnique : public virtual ITypeConstraint {
public:

    virtual ~ITypeConstraintUnique() { }

    virtual const std::vector<ITypeExprUP> &getExprs() const = 0;

};

}
}

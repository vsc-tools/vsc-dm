
#pragma once
#include "vsc/dm/IModelConstraintScope.h"

namespace vsc {
namespace dm {

class IModelConstraintSubst : public virtual IModelConstraintScope {
public:

    virtual ~IModelConstraintSubst() { }

    virtual IModelConstraint *getOriginal() const = 0;

    virtual IModelConstraint *releaseOriginal() = 0;

};

}
}

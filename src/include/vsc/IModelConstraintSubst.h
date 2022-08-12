
#pragma once
#include "vsc/IModelConstraintScope.h"

namespace vsc {

class IModelConstraintSubst : public virtual IModelConstraintScope {
public:

    virtual ~IModelConstraintSubst() { }

    virtual IModelConstraint *getOriginal() const = 0;

    virtual IModelConstraint *releaseOriginal() = 0;

};

}
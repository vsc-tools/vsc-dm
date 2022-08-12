
#pragma once
#include "vsc/IModelConstraint.h"

namespace vsc {

class IModelConstraintRef : public virtual IModelConstraint {
public:

    virtual ~IModelConstraintRef() { }

    virtual IModelConstraint *getTarget() const = 0;

};

}


#pragma once
#include "vsc/dm/IModelConstraint.h"

namespace vsc {
namespace dm {

class IModelConstraintRef : public virtual IModelConstraint {
public:

    virtual ~IModelConstraintRef() { }

    virtual IModelConstraint *getTarget() const = 0;

};

}
}

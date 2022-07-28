
#pragma once
#include "vsc/IModelConstraintRef.h"
#include "ModelConstraint.h"

namespace vsc {

class ModelConstraintRef : public virtual IModelConstraintRef, public ModelConstraint {
public:
    ModelConstraintRef(IModelConstraint *target);

    virtual ~ModelConstraintRef();

    virtual IModelConstraint *getTarget() const override { return m_target.get(); }

    virtual void accept(IVisitor *v) override { v->visitModelConstraintRef(this); }

private:
    IModelConstraintUP              m_target;

};

}

#pragma once
#include "vsc/dm/IModelConstraintSubst.h"
#include "ModelConstraintScope.h"


namespace vsc {
namespace dm {

class ModelConstraintSubst : 
    public virtual IModelConstraintSubst, 
    public virtual ModelConstraintScope {
public:

    ModelConstraintSubst(IModelConstraint *orig);

    virtual ~ModelConstraintSubst();

    virtual IModelConstraint *getOriginal() const override {
        return m_original.get();
    }

    virtual IModelConstraint *releaseOriginal() override {
        return m_original.release();
    }

    virtual void accept(IVisitor *v) override { v->visitModelConstraintSubst(this); }

private:
    IModelConstraintUP              m_original;

};

}
}

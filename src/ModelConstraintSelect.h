
#pragma once
#include "vsc/IContext.h"
#include "vsc/IModelConstraintSelect.h"
#include "vsc/IModelField.h"
#include "ModelConstraint.h"

namespace vsc {

class ModelConstraintSelect : 
    public virtual IModelConstraintSelect, 
    public virtual ModelConstraint {
public:

    ModelConstraintSelect(
        IContext            *ctxt,
        IModelField         *lhs);

    virtual ~ModelConstraintSelect();


    virtual IModelField *getLhs() const override { return m_lhs; }

    virtual const std::vector<IModelField *> &getRhs() const override {
        return m_rhs;
    }

    virtual void addRhs(IModelField *rhs) override;

    virtual IModelField *getSelector() override {
        return m_selector.get();
    }

    virtual void accept(IVisitor *v) override { v->visitModelConstraintSelect(this); }

private:
    IModelFieldUP               m_selector;
    IModelField                 *m_lhs;
    std::vector<IModelField *>  m_rhs;

};


}
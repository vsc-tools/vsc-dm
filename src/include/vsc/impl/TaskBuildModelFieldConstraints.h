
#pragma once
#include "vsc/IModelBuildContext.h"
#include "vsc/impl/TaskBuildModelConstraint.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

template <class ConstraintBuilderT=TaskBuildModelConstraint<> > 
    class TaskBuildModelFieldConstraints : 
        public virtual VisitorBase {
public:

    TaskBuildModelFieldConstraints(IModelBuildContext *ctxt) : 
        m_ctxt(ctxt), m_constraint_builder(ctxt) { }

    void build(IModelField *model, IDataType *type) {
        m_ctxt->pushTopDownScope(model);
        type->accept(m_this);
        m_ctxt->popTopDownScope();
    }

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
        for (std::vector<ITypeConstraintUP>::const_iterator
            it=t->getConstraints().begin();
            it!=t->getConstraints().end(); it++) {
            IModelConstraint *c = m_constraint_builder.build(it->get());
        }
    }


protected:
    IModelBuildContext                  *m_ctxt;
    ConstraintBuilderT                  m_constraint_builder;
};

}
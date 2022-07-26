
#pragma once
#include "vsc/impl/VisitorBase.h"

namespace vsc {

/**
 * @brief Resolve a field-reference expression to a field
 * 
 */
class TaskResolveModelExprFieldRef : public virtual VisitorBase {
public:

    TaskResolveModelExprFieldRef() { }

    virtual ~TaskResolveModelExprFieldRef() { }

    IModelField *resolve(IModelField *base, IModelExpr *e) {
        m_field = base;
        e->accept(m_this);
        return m_field;
    }

	virtual void visitModelExprBin(IModelExprBin *e) override {
        m_field = 0;
    }

	virtual void visitModelExprCond(IModelExprCond *e) override {
        m_field = 0;
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        m_field = e->field();
    }

	virtual void visitModelExprIn(IModelExprIn *e) override {
        m_field = 0;
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {
        IModelField *field = m_field;

        if (!field) {
            return;
        }

        for (std::vector<ModelExprIndexedFieldRefElem>::const_iterator
            it=e->getPath().begin();
            it!=e->getPath().end(); it++) {

        }
    }

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override {
        m_field = 0;
    }

	virtual void visitModelExprRange(IModelExprRange *e) override {
        m_field = 0;
    }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override {
        m_field = 0;
    }

	virtual void visitModelExprRef(IModelExprRef *e) override {
        m_field = 0;
    }

	virtual void visitModelExprUnary(IModelExprUnary *e) override {
        m_field = 0;
    }

	virtual void visitModelExprVal(IModelExprVal *e) override [
        m_field = 0;
    ]


private:
    IModelField                     *m_field;

};

}
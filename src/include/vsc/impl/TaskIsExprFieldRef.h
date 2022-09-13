
#pragma once
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskIsExprFieldRef : public virtual VisitorBase {
public:

    TaskIsExprFieldRef() : m_field(0) { }

    virtual ~TaskIsExprFieldRef() { }

    IModelField *check(IModelExpr *e) {
        m_field = 0;
        e->accept(m_this);
        return m_field;
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        m_field = e->field();
    }

private:
    IModelField                 *m_field;

};

}
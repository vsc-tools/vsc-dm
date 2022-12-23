
#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

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
}

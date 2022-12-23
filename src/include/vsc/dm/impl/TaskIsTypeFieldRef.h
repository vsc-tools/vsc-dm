
#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class TaskIsTypeFieldRef : public virtual VisitorBase {
public:

    TaskIsTypeFieldRef() : m_ret(false) { }

    bool eval(ITypeField *f) {
        m_ret = false;
        f->accept(m_this);
        return m_ret;
    }

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override { }

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
        m_ret = true;
    }

protected:
    bool                    m_ret;

};

}
}

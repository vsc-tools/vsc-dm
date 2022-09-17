
#pragma once
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskIsModelFieldRef : public virtual VisitorBase {
public:

    TaskIsModelFieldRef() : m_ret(false) { }


    bool check(IModelField *f) {
        m_ret = false;
        f->accept(m_this);
        return m_ret;
    }

	virtual void visitModelField(IModelField *f) override { }

	virtual void visitModelFieldRef(IModelFieldRef *f) override {
        m_ret = true;
    }

	virtual void visitModelFieldRefRoot(IModelFieldRef *f) override {
        m_ret = true;
    }

	virtual void visitModelFieldRefType(IModelFieldRef *f) override {
        m_ret = true;
    }

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override {
        m_ret = true;
    }

protected:
    bool                    m_ret;

};

}
/*
 * TaskResolveFieldRefExpr.h
 *
 *  Created on: Jun 19, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/impl/VisitorBase.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelField.h"
#include "vsc/dm/ITypeExprFieldRef.h"

namespace vsc {
namespace dm {

class TaskResolveFieldRefExpr : public VisitorBase {
public:

	TaskResolveFieldRefExpr(IModelBuildContext *ctxt, IVisitor *this_p=0) :
		VisitorBase(this_p), m_ctxt(ctxt), m_field(0) { }

	virtual ~TaskResolveFieldRefExpr() { }

	IModelField *resolve(ITypeExpr *target) {
		m_field = 0;

		target->accept(m_this);

		return m_field;
	}

	template <class T> T *resolveT(ITypeExpr *target) {
		return dynamic_cast<T *>(resolve(target));
	}

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override {
        switch (e->getRootRefKind()) {
            case ITypeExprFieldRef::RootRefKind::TopDownScope:
				m_field = m_ctxt->getTopDownScope();
                break;
            case ITypeExprFieldRef::RootRefKind::BottomUpScope:
				m_field = m_ctxt->getScope();
                break;
        }
        m_field = m_field->getField(e->getSubFieldIndex());
	}

protected:
	IModelBuildContext					*m_ctxt;
	IModelField							*m_field;

};

}
}

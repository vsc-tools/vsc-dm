/*
 * TaskResolveFieldRefExpr.h
 *
 *  Created on: Jun 19, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/impl/VisitorBase.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/IModelField.h"
#include "vsc/ITypeExprFieldRef.h"

namespace vsc {

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
		for (std::vector<TypeExprFieldRefElem>::const_reverse_iterator
			it=e->getPath().rbegin(); it!=e->getPath().rend(); it++) {
			switch (it->kind) {
			case TypeExprFieldRefElemKind::Root: {
				m_field = m_ctxt->getTopDownScope();
			} break;
			case TypeExprFieldRefElemKind::ActiveScope: {
				m_field = m_ctxt->getScope();
			} break;
			case TypeExprFieldRefElemKind::IdxOffset: {
				m_field = m_field->getField(it->idx);
			} break;

			default:
				fprintf(stdout, "Unhandled case\n");
			}
		}
	}

protected:
	IModelBuildContext					*m_ctxt;
	IModelField							*m_field;

};

}

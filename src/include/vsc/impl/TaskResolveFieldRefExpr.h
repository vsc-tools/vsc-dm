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

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override {
		for (auto it=e->getPath().begin(); it!=e->getPath().end(); it++) {
			switch (it->kind) {
			case TypeExprFieldRefElemKind::Root: {
				m_field = m_ctxt->getField(-1);
			} break;
			case TypeExprFieldRefElemKind::ActiveScope: {
				m_field = m_ctxt->getField(it->idx);
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

/*
 * TaskBuildModelExpr.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelBuildContext.h"
#include "vsc/impl/VisitorBase.h"


namespace vsc {

class TaskBuildModelExpr : public VisitorBase {
public:
	TaskBuildModelExpr(
			IModelBuildContext	*ctxt,
			IVisitor			*this_p=0):
				VisitorBase(this_p), m_ctxt(ctxt), m_expr(0) { }

	virtual ~TaskBuildModelExpr() { }

	virtual IModelExpr *build(ITypeExpr *e) { return expr(e); }

	virtual void visitTypeExprBin(ITypeExprBin *e) override {
		IModelExpr *lhs = expr(e->lhs());
		IModelExpr *rhs = expr(e->rhs());
		m_expr = m_ctxt->ctxt()->mkModelExprBin(lhs, e->op(), rhs);
	}

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override {
		IModelField *f = 0;
		for (auto it=e->getPath().rbegin(); it!=e->getPath().rend(); it++) {
			switch (it->kind) {
			case TypeExprFieldRefElemKind::Root: {
				f = m_ctxt->getField(-1);
			} break;
			case TypeExprFieldRefElemKind::ActiveScope: {
				f = m_ctxt->getField(it->idx);
			} break;
			case TypeExprFieldRefElemKind::IdxOffset: {
				f = m_ctxt->getField(-1)->getField(it->idx);
			} break;

			default:
				fprintf(stdout, "Unhandled case\n");
			}
		}

		m_expr = m_ctxt->ctxt()->mkModelExprFieldRef(f);
	}

	virtual void visitTypeExprVal(ITypeExprVal *e) override {
		m_expr = m_ctxt->ctxt()->mkModelExprVal(e->val());
	}

	virtual void visitTypeField(ITypeField *f) override {
		;
	}

protected:
	virtual IModelExpr *expr(ITypeExpr *expr) {
		m_expr = 0;
		expr->accept(m_this);
		return m_expr;
	}

protected:
	IModelBuildContext			*m_ctxt;
	IModelExpr					*m_expr;

};

}

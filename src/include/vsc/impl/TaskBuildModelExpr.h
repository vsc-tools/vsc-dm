/*
 * TaskBuildModelExpr.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"
#include "vsc/impl/VisitorBase.h"


namespace vsc {

class TaskBuildModelExpr : public VisitorBase {
public:
	TaskBuildModelExpr(
			IContext		*ctxt,
			IModelField 	*scope,
			IVisitor		*this_p=0):
				VisitorBase(this_p), m_ctxt(ctxt), m_scope(scope), m_expr(0) { }

	virtual ~TaskBuildModelExpr() { }

	virtual IModelExpr *build(ITypeExpr *e) { return expr(e); }

	virtual void visitTypeExprBin(ITypeExprBin *e) override {
		IModelExpr *lhs = expr(e->lhs());
		IModelExpr *rhs = expr(e->rhs());
		m_expr = m_ctxt->mkModelExprBin(lhs, e->op(), rhs);
	}

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override {
		IModelField *f = 0;
		for (auto it=e->getPath().rbegin(); it!=e->getPath().rend(); it++) {
			switch (it->kind) {
			case TypeExprFieldRefElemKind::Root: {
				f = m_scope;
			} break;
			case TypeExprFieldRefElemKind::IdxOffset: {
				f = m_scope->getField(it->idx);
			} break;

			default:
				fprintf(stdout, "Unhandled case\n");
			}
		}

		m_expr = m_ctxt->mkModelExprFieldRef(f);
	}

	virtual void visitTypeExprVal(ITypeExprVal *e) override {
		m_expr = m_ctxt->mkModelExprVal(e->val());
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
	IContext					*m_ctxt;
	IModelField					*m_scope;
	IModelExpr					*m_expr;

};

}

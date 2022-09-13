/*
 * TaskBuildModelExpr.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelBuildContext.h"
#include "vsc/ITypeExprFieldRef.h"
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

	template <class T> T *buildT(ITypeExpr *e) {
		return dynamic_cast<T *>(build(e));
	}

	virtual void visitTypeExprBin(ITypeExprBin *e) override {
		IModelExpr *lhs = expr(e->lhs());
		IModelExpr *rhs = expr(e->rhs());
		m_expr = m_ctxt->ctxt()->mkModelExprBin(lhs, e->op(), rhs);
	}

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override {
		bool references_ref_fields = false;

		IModelField *f = 0;
		for (auto it=e->getPath().rbegin(); it!=e->getPath().rend(); it++) {
			switch (it->kind) {
			case TypeExprFieldRefElemKind::Root: {
				f = m_ctxt->getTopDownScope();
			} break;
			case TypeExprFieldRefElemKind::ActiveScope: {
				f = m_ctxt->getBottomUpScope(it->idx);
			} break;
			case TypeExprFieldRefElemKind::IdxOffset: {
				f = f->getField(it->idx);
			} break;

			default:
				fprintf(stdout, "Unhandled case\n");
			}
		}

		m_expr = m_ctxt->ctxt()->mkModelExprFieldRef(f);
	}

	virtual void visitTypeExprRangelist(ITypeExprRangelist *e) override {
		IModelExprRangelist *rl = m_ctxt->ctxt()->mkModelExprRangelist();

		// TODO: Should really have a 'const' variant where everything
		// just flattens out

		for (std::vector<ITypeExprRangeUP>::const_iterator
				it=e->getRanges().begin();
				it!=e->getRanges().end(); it++) {
			if ((*it)->isSingle()) {
				rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						true,
						expr((*it)->lower()),
						0));
			} else {
				if ((*it)->lower() && (*it)->upper()) {
					IModelExpr *lower = expr((*it)->lower());
					IModelExpr *upper = expr((*it)->upper());

					rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						false,
						lower,
						upper));
				} else if ((*it)->lower()) {
					rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						false,
						expr((*it)->lower()),
						0));
				} else {
					rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						false,
						0,
						expr((*it)->upper())));
				}
			}
		}

		m_expr = rl;
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

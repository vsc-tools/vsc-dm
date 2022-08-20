/*
 * TaskBuildModelConstraint.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelBuildContext.h"
#include "vsc/IModelConstraint.h"
#include "vsc/ITypeConstraint.h"
#include "vsc/impl/TaskBuildModelExpr.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

template <class ModelExprBuilderT=TaskBuildModelExpr> 
	class TaskBuildModelConstraint : public VisitorBase {
public:

	TaskBuildModelConstraint(
			IModelBuildContext		*ctxt,
			IVisitor				*this_p=0) :
				VisitorBase(this_p), m_ctxt(ctxt), 
				m_expr_builder(ctxt), m_constraint(0)  { }

	virtual ~TaskBuildModelConstraint() { }

	virtual IModelConstraint *build(ITypeConstraint *c) {
		m_constraint = 0;
		m_constraint_s.clear();
		c->accept(this);
		return m_constraint;
	}

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) override {
		IModelConstraintBlock *cm = m_ctxt->ctxt()->mkModelConstraintBlock(c->name());

		if (!m_constraint) {
			m_constraint = cm;
		}

		m_constraint_s.push_back(cm);
		for (auto it=c->constraints().begin(); it!=c->constraints().end(); it++) {
			(*it)->accept(m_this);
		}

		m_constraint_s.pop_back();

		if (m_constraint_s.size() == 0) {
			m_ctxt->getField(-1)->addConstraint(cm);
		}
	}

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override {
		// Convert type expression to a model expression
		IModelExpr *expr = m_expr_builder.build(c->expr());

		IModelConstraintExpr *cm = m_ctxt->ctxt()->mkModelConstraintExpr(expr);

		if (!m_constraint) {
			m_constraint = cm;
		}

		if (m_constraint_s.size()) {
			m_constraint_s.back()->addConstraint(cm);
		}
	}

	virtual void visitTypeConstraintIfElse(ITypeConstraintIfElse *c) override {
		IModelExpr *cond = m_expr_builder.build(c->getCond());

		IModelConstraintScope *true_c = m_ctxt->ctxt()->mkModelConstraintScope();
		m_constraint_s.push_back(true_c);
		c->getTrue()->accept(m_this);
		m_constraint_s.pop_back();

		IModelConstraintScope *false_c = 0;

		if (c->getFalse()) {
			false_c = m_ctxt->ctxt()->mkModelConstraintScope();
			m_constraint_s.push_back(false_c);
			c->getFalse()->accept(m_this);
			m_constraint_s.pop_back();
		}

		IModelConstraintIfElse *cm = m_ctxt->ctxt()->mkModelConstraintIfElse(
			cond,
			true_c,
			false_c);

		if (!m_constraint) {
			m_constraint = cm;
		}

		if (m_constraint_s.size()) {
			m_constraint_s.back()->addConstraint(cm);
		}
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
		VisitorBase::visitTypeConstraintScope(c);
	}

protected:
	IModelBuildContext							*m_ctxt;
	ModelExprBuilderT							m_expr_builder;
	std::vector<IModelConstraintScope *>		m_constraint_s;
	IModelConstraint							*m_constraint;

};

}

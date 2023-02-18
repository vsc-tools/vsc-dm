/*
 * TaskBuildModelConstraint.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 * 
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#pragma once
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelConstraint.h"
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/impl/TaskBuildModelExpr.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

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
		for (std::vector<ITypeConstraintUP>::const_iterator
            it=c->getConstraints().begin(); 
            it!=c->getConstraints().end(); it++) {
			(*it)->accept(m_this);
		}

		m_constraint_s.pop_back();

/*
		if (m_constraint_s.size() == 0) {
			m_ctxt->getTopDownScope()->addConstraint(cm, true);
		}
 */
	}

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override {
		// Convert type expression to a model expression
		IModelExpr *expr = m_expr_builder.build(c->expr());

		IModelConstraintExpr *cm = m_ctxt->ctxt()->mkModelConstraintExpr(expr);

		if (!m_constraint) {
			m_constraint = cm;
		}

		if (m_constraint_s.size()) {
			m_constraint_s.back()->addConstraint(cm, true);
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
			m_constraint_s.back()->addConstraint(cm, true);
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
}

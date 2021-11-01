/*
 * ModelConstraintIf.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"
#include "ModelConstraint.h"
#include "ModelConstraintScope.h"

namespace vsc {

class ModelConstraintIf : public ModelConstraint {
public:
	ModelConstraintIf(
			ModelExpr				*cond,
			ModelConstraint			*true_c,
			ModelConstraint			*false_c);

	virtual ~ModelConstraintIf();

	ModelExpr *cond() const { return m_cond.get(); }

	ModelConstraint *true_c() const { return m_true_c.get(); }

	void true_c(ModelConstraint *c) {
		m_true_c = ModelConstraintUP(c);
	}

	ModelConstraint *false_c() const { return m_false_c.get(); }

	void false_c(ModelConstraint *c) {
		m_false_c = ModelConstraintUP(c);
	}

	virtual void accept(IVisitor *v) override { v->visitModelConstraintIf(this); }

private:
	ModelExprUP						m_cond;
	ModelConstraintUP				m_true_c;
	ModelConstraintUP				m_false_c;

};

} /* namespace vsc */


/*
 * ModelConstraintIf.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"
#include "vsc/IModelConstraint.h"
#include "ModelExpr.h"
#include "ModelConstraint.h"
#include "ModelConstraintScope.h"

namespace vsc {

class ModelConstraintIf : public ModelConstraint {
public:
	ModelConstraintIf(
			IModelExpr				*cond,
			IModelConstraint		*true_c,
			IModelConstraint		*false_c);

	virtual ~ModelConstraintIf();

	IModelExpr *cond() const { return m_cond.get(); }

	IModelConstraint *true_c() const { return m_true_c.get(); }

	void true_c(IModelConstraint *c) {
		m_true_c = IModelConstraintUP(c);
	}

	IModelConstraint *false_c() const { return m_false_c.get(); }

	void false_c(IModelConstraint *c) {
		m_false_c = IModelConstraintUP(c);
	}

	virtual void accept(IVisitor *v) override { v->visitModelConstraintIf(this); }

private:
	IModelExprUP					m_cond;
	IModelConstraintUP				m_true_c;
	IModelConstraintUP				m_false_c;

};

} /* namespace vsc */


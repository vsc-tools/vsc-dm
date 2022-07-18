/*
 * ModelConstraintIfElse.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraintIfElse.h"
#include "ModelExpr.h"
#include "ModelConstraint.h"
#include "ModelConstraintScope.h"

namespace vsc {

class ModelConstraintIfElse : public IModelConstraintIfElse {
public:
	ModelConstraintIf(
			IModelExpr				*cond,
			IModelConstraint		*true_c,
			IModelConstraint		*false_c);

	virtual ~ModelConstraintIfElse();

	virtual IModelExpr *cond() const override {
		return m_cond.get();
	}

	virtual IModelConstraint *getTrue() const override {
		return m_true_c.get();
	}

	virtual void setTrue(IModelConstraint *c) override {
		m_true_c = IModelConstraintUP(c);
	}

	virtual IModelConstraint *getFalse() const override {
		return m_false_c.get();
	}

	virtual void setFalse(IModelConstraint *c) override {
		m_false_c = IModelConstraintUP(c);
	}

	virtual void accept(IVisitor *v) override { v->visitModelConstraintIfElse(this); }

private:
	IModelExprUP					m_cond;
	IModelConstraintUP				m_true_c;
	IModelConstraintUP				m_false_c;

};

} /* namespace vsc */


/*
 * ModelConstraintImplies.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelConstraint.h"
#include "ModelExpr.h"

namespace vsc {

class ModelConstraintImplies : public ModelConstraint {
public:
	ModelConstraintImplies(
			ModelExpr			*cond,
			ModelConstraint		*body);

	virtual ~ModelConstraintImplies();

	ModelExpr *cond() const { return m_cond.get(); }

	ModelConstraint *body() const { return m_body.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelConstraintImplies(this); }

private:
	ModelExprUP					m_cond;
	ModelConstraintUP			m_body;
};

} /* namespace vsc */


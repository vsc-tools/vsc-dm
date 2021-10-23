/*
 * ModelConstraintSoft.h
 *
 *  Created on: Oct 8, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelConstraint.h"
#include "ModelConstraintExpr.h"

namespace vsc {

class ModelConstraintSoft : public ModelConstraint {
public:
	ModelConstraintSoft(ModelConstraintExpr *constraint);

	virtual ~ModelConstraintSoft();

	ModelConstraintExpr *constraint() const { return m_constraint.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelConstraintSoft(this); }

private:
	ModelConstraintExprUP			m_constraint;
};

} /* namespace vsc */


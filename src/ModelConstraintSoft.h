/*
 * ModelConstraintSoft.h
 *
 *  Created on: Oct 8, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraintSoft.h"
#include "ModelConstraint.h"
#include "ModelConstraintExpr.h"

namespace vsc {

class ModelConstraintSoft : public IModelConstraintSoft {
public:
	ModelConstraintSoft(ModelConstraintExpr *constraint);

	virtual ~ModelConstraintSoft();

	virtual IModelConstraintExpr *constraint() const override {
		return m_constraint.get();
	}

	virtual void accept(IVisitor *v) override { v->visitModelConstraintSoft(this); }

private:
	IModelConstraintExprUP			m_constraint;
};

} /* namespace vsc */


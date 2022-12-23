/*
 * ModelConstraintSoft.h
 *
 *  Created on: Oct 8, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelConstraintSoft.h"
#include "ModelConstraint.h"
#include "ModelConstraintExpr.h"

namespace vsc {
namespace dm {

class ModelConstraintSoft : 
	public virtual IModelConstraintSoft,
	public virtual ModelConstraint {
public:
	ModelConstraintSoft(IModelConstraintExpr *constraint, int32_t priority=-1);

	virtual ~ModelConstraintSoft();

	virtual IModelConstraintExpr *constraint() const override {
		return m_constraint.get();
	}

	virtual int32_t getPriority() const override { return m_priority; }

	virtual void accept(IVisitor *v) override { v->visitModelConstraintSoft(this); }

private:
	IModelConstraintExprUP			m_constraint;
	int32_t							m_priority;
};

}
} /* namespace vsc */


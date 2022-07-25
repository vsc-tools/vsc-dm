/*
 * ModelConstraintImplies.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraintImplies.h"
#include "ModelConstraint.h"

namespace vsc {

class ModelConstraintImplies : 
	public virtual IModelConstraintImplies,
	public virtual ModelConstraint {
public:
	ModelConstraintImplies(
			IModelExpr			*cond,
			IModelConstraint	*body);

	virtual ~ModelConstraintImplies();

	virtual IModelExpr *getCond() const override { return m_cond.get(); }

	virtual IModelConstraint *getBody() const override { return m_body.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelConstraintImplies(this); }

private:
	IModelExprUP				m_cond;
	IModelConstraintUP			m_body;
};

} /* namespace vsc */


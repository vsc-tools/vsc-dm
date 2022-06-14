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
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskBuildModelConstraint : public VisitorBase {
public:

	TaskBuildModelConstraint(
			IModelBuildContext		*ctxt) : m_ctxt(ctxt), m_constraint(0)  { }

	virtual ~TaskBuildModelConstraint() { }

	virtual IModelConstraint *build(ITypeConstraint *c) {
		m_constraint = 0;
		c->accept(this);
		return m_constraint;
	}

protected:
	IModelBuildContext				*m_ctxt;
	IModelConstraint				*m_constraint;

};

}

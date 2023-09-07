/*
 * ModelConstraintForeach.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelConstraintForeach.h"
#include "vsc/dm/IContext.h"
#include "ModelConstraintScope.h"

namespace vsc {
namespace dm {

class ModelConstraintForeach : 
	public virtual IModelConstraintForeach,
	public virtual ModelConstraintScope {
public:
	ModelConstraintForeach(
		IContext 			*ctxt,
		IModelExpr			*target,
		const std::string	&index_name = "");

	virtual ~ModelConstraintForeach();

	virtual IModelExpr *getTarget() const override { return m_target.get(); }

	virtual IModelField *getIndexIt() const override { return m_index_it.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelConstraintForeach(this); }

private:
	IModelExprUP					m_target;
	IModelFieldUP					m_index_it;

};

}
} /* namespace vsc */


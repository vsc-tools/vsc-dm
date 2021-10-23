/*
 * ModelConstraintScope.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ModelConstraint.h"

namespace vsc {

class ModelConstraintScope;
using ModelConstraintScopeUP=std::unique_ptr<ModelConstraintScope>;
class ModelConstraintScope : public ModelConstraint {
public:
	ModelConstraintScope();

	virtual ~ModelConstraintScope();

	const std::vector<ModelConstraintUP> &constraints() const {
		return m_constraints;
	}

	void add_constraint(ModelConstraint *c);

	virtual void accept(IVisitor *v) override { v->visitModelConstraintScope(this); }

private:
	std::vector<ModelConstraintUP>		m_constraints;
};

} /* namespace vsc */


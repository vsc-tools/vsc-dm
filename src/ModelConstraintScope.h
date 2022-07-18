/*
 * ModelConstraintScope.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IModelConstraintScope.h"
#include "ModelConstraint.h"

namespace vsc {

class ModelConstraintScope;
using ModelConstraintScopeUP=std::unique_ptr<ModelConstraintScope>;
class ModelConstraintScope : public IModelConstraintScope {
public:
	ModelConstraintScope();

	virtual ~ModelConstraintScope();

	virtual const std::vector<IModelConstraintUP> &constraints() const override {
		return m_constraints;
	}

	virtual void addConstraint(IModelConstraint *c) override;

	virtual void accept(IVisitor *v) override { v->visitModelConstraintScope(this); }

private:
	std::vector<IModelConstraintUP>		m_constraints;
};

} /* namespace vsc */


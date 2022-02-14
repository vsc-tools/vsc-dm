/*
 * ModelConstraintBlock.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraintBlock.h"
#include "ModelConstraintScope.h"

namespace vsc {

class ModelConstraintBlock : public IModelConstraintBlock {
public:
	ModelConstraintBlock(const std::string &name);

	virtual ~ModelConstraintBlock();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual const std::vector<IModelConstraintUP> &constraints() const override {
		return m_constraints;
	}

	virtual void add_constraint(IModelConstraint *c) override;

	virtual void accept(IVisitor *v) override { v->visitModelConstraintBlock(this); }

private:
	std::string							m_name;
	std::vector<IModelConstraintUP>		m_constraints;
};

} /* namespace vsc */


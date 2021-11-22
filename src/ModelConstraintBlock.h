/*
 * ModelConstraintBlock.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelConstraintScope.h"

namespace vsc {

class ModelConstraintBlock : public ModelConstraintScope {
public:
	ModelConstraintBlock(const std::string &name);

	virtual ~ModelConstraintBlock();

	const std::string &name() const { return m_name; }

	virtual void accept(IVisitor *v) override { v->visitModelConstraintBlock(this); }

private:
	std::string						m_name;
};

} /* namespace vsc */


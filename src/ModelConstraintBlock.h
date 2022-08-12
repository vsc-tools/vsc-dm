/*
 * ModelConstraintBlock.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "vsc/IModelConstraintBlock.h"
#include "ModelConstraintScope.h"

namespace vsc {

class ModelConstraintBlock : 
	public virtual IModelConstraintBlock, 
	public virtual ModelConstraintScope {
public:
	ModelConstraintBlock(const std::string &name);

	virtual ~ModelConstraintBlock();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual void accept(IVisitor *v) override { v->visitModelConstraintBlock(this); }

private:
	std::string							m_name;
};

} /* namespace vsc */


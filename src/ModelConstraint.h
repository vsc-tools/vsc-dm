/*
 * ModelConstraint.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IModelConstraint.h"

namespace vsc {

class ModelConstraint;
using ModelConstraintUP=std::unique_ptr<ModelConstraint>;
class ModelConstraint : public virtual IModelConstraint {
public:
	ModelConstraint();

	virtual ~ModelConstraint();

	virtual IModelConstraint *getParent() const override {
		return m_parent;
	}

	virtual void setParent(IModelConstraint *c) override {
		m_parent = c;
	}

	virtual void accept(IVisitor *v) override { v->visitModelConstraint(this); }

private:
	IModelConstraint			*m_parent;

};

} /* namespace vsc */


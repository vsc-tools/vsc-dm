/*
 * ModelConstraint.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IAccept.h"

namespace vsc {

class ModelConstraint;
using ModelConstraintUP=std::unique_ptr<ModelConstraint>;
class ModelConstraint : public virtual IAccept {
public:
	ModelConstraint();

	virtual ~ModelConstraint();

	virtual void accept(IVisitor *v) override { v->visitModelConstraint(this); }

};

} /* namespace vsc */


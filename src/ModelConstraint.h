/*
 * ModelConstraint.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>

namespace vsc {

class ModelConstraint;
using ModelConstraintUP=std::unique_ptr<ModelConstraint>;
class ModelConstraint {
public:
	ModelConstraint();

	virtual ~ModelConstraint();

};

} /* namespace vsc */


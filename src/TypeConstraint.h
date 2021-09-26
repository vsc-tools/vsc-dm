/*
 * TypeConstraint.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>

namespace vsc {

class TypeConstraint;
using TypeConstraintUP=std::unique_ptr<TypeConstraint>;
class TypeConstraint {
public:
	TypeConstraint();

	virtual ~TypeConstraint();

};

} /* namespace vsc */


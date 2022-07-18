/*
 * IModelConstraintScope.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IModelConstraint.h"

namespace vsc {

class IModelConstraintScope;
using IModelConstraintScopeUP=std::unique_ptr<IModelConstraintScope>;
class IModelConstraintScope : public IModelConstraint {
public:
	virtual ~IModelConstraintScope() { }

	virtual const std::vector<IModelConstraintUP> &constraints() const = 0;

	virtual void addConstraint(IModelConstraint *c) = 0;
};

}

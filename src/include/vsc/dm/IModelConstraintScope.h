/*
 * IModelConstraintScope.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/dm/IModelConstraint.h"

namespace vsc {
namespace dm {

class IModelConstraintScope;
using IModelConstraintScopeUP=std::unique_ptr<IModelConstraintScope>;
class IModelConstraintScope : public virtual IModelConstraint {
public:
	virtual ~IModelConstraintScope() { }

	virtual const std::vector<IModelConstraintUP> &constraints() const = 0;

	/**
	 */
	virtual IModelConstraint *swapConstraint(
		uint32_t			idx,
		IModelConstraint	*c) = 0;

	virtual void addConstraint(IModelConstraint *c) = 0;
};

}
}

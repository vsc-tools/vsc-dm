/*
 * IModelConstraintImplies.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraint.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelConstraintImplies;
using IModelConstraintImpliesUP=std::unique_ptr<IModelConstraintImplies>;
class IModelConstraintImplies : public IModelConstraint {
public:

	virtual ~IModelConstraintImplies() { }

	virtual IModelExpr *cond() const = 0;

	virtual IModelConstraint *body() const = 0;

};

}

/*
 * IModelConstraintIf.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraint.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelConstraintIfElse;
using IModelConstraintIfElseUP=std::unique_ptr<IModelConstraintIfElse>;
class IModelConstraintIfElse : public virtual IModelConstraint {
public:

	virtual ~IModelConstraintIfElse() { }

	virtual IModelExpr *getCond() const = 0;

	virtual IModelConstraint *getTrue() const = 0;

	virtual void setTrue(IModelConstraint *c) = 0;

	virtual IModelConstraint *getFalse() const = 0;

	virtual void setFalse(IModelConstraint *c) = 0;


};
}

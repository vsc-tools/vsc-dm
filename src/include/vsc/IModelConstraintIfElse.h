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

class IModelConstraintIf;
using IModelConstraintIfUP=std::unique_ptr<IModelConstraintIf>;
class IModelConstraintIf : public IModelConstraint {
public:

	virtual ~IModelConstraintIf() { }

	virtual IModelExpr *cond() const = 0;

	virtual IModelConstraint *getTrue() const = 0;

	virtual void setTrue(IModelConstraint *c) = 0;

	virtual IModelConstraint *getFalse() const = 0;

	virtual void setFalse(IModelConstraint *c) = 0;


};
}

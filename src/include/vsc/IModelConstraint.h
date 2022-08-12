/*
 * IModelConstraint.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IAccept.h"

namespace vsc {

class IModelConstraint;
using IModelConstraintUP=std::unique_ptr<IModelConstraint>;
class IModelConstraint : public IAccept {
public:

	virtual ~IModelConstraint() { }

	virtual IModelConstraint *getParent() const = 0;

	virtual void setParent(IModelConstraint *c) = 0;

};

}


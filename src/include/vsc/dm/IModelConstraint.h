/*
 * IModelConstraint.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IAccept.h"

namespace vsc {
namespace dm {

class IModelConstraint;
using IModelConstraintUP=UP<IModelConstraint>;
class IModelConstraint : public IAccept {
public:

	virtual ~IModelConstraint() { }

	virtual IModelConstraint *getParent() const = 0;

	virtual void setParent(IModelConstraint *c) = 0;

};

}
}


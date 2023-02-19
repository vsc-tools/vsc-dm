/*
 * IModelConstraintImplies.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelConstraint.h"
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelConstraintImplies;
using IModelConstraintImpliesUP=UP<IModelConstraintImplies>;
class IModelConstraintImplies : public virtual IModelConstraint {
public:

	virtual ~IModelConstraintImplies() { }

	virtual IModelExpr *getCond() const = 0;

	virtual IModelConstraint *getBody() const = 0;

};

}
}

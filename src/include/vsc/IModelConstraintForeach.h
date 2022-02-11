/*
 * IModelConstraintForeach.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraint.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelConstraintForeach;
using IModelConstraintForeachUP=std::unique_ptr<IModelConstraintForeach>;
class IModelConstraintForeach : public IModelConstraint {
public:

	virtual ~IModelConstraintForeach() { }

};

}

/*
 * IModelConstraintForeach.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraintScope.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelConstraintForeach;
using IModelConstraintForeachUP=std::unique_ptr<IModelConstraintForeach>;
class IModelConstraintForeach : public virtual IModelConstraintScope {
public:

	virtual ~IModelConstraintForeach() { }

	virtual IModelExpr *getTarget() const = 0;

};

}

/*
 * IModelConstraintForeach.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelConstraintScope.h"
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelConstraintForeach;
using IModelConstraintForeachUP=UP<IModelConstraintForeach>;
class IModelConstraintForeach : public virtual IModelConstraintScope {
public:

	virtual ~IModelConstraintForeach() { }

	virtual IModelExpr *getTarget() const = 0;

	/**
	 * @brief Returns the index-iteration variable
	 * 
	 * @return IModelField* 
	 */
	virtual IModelField *getIndexIt() const = 0;

};

}
}

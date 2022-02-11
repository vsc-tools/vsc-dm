/*
 * IModelConstraintExpr.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraint.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelConstraintExpr : public IModelConstraint {
public:

	virtual ~IModelConstraintExpr() { }

	virtual IModelExpr *expr() const = 0;

};

}

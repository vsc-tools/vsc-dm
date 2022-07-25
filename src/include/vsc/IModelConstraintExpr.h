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

class IModelConstraintExpr;
using IModelConstraintExprUP=std::unique_ptr<IModelConstraintExpr>;
class IModelConstraintExpr : public virtual IModelConstraint {
public:

	virtual ~IModelConstraintExpr() { }

	virtual IModelExpr *expr() const = 0;

};

}

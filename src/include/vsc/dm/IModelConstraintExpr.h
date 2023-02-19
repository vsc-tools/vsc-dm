/*
 * IModelConstraintExpr.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelConstraint.h"
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelConstraintExpr;
using IModelConstraintExprUP=UP<IModelConstraintExpr>;
class IModelConstraintExpr : public virtual IModelConstraint {
public:

	virtual ~IModelConstraintExpr() { }

	virtual IModelExpr *expr() const = 0;

};

}
}

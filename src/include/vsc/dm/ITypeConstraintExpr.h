/*
 * ITypeConstraintExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class ITypeConstraintExpr;
using ITypeConstraintExprUP=UP<ITypeConstraintExpr>;
class ITypeConstraintExpr : public ITypeConstraint {
public:

	virtual ~ITypeConstraintExpr() { }

	virtual ITypeExpr *expr() const = 0;

};

}
}

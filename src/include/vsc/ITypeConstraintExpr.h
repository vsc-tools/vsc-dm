/*
 * ITypeConstraintExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/ITypeConstraint.h"
#include "vsc/ITypeExpr.h"

namespace vsc {

class ITypeConstraintExpr;
using ITypeConstraintExprUP=std::unique_ptr<ITypeConstraintExpr>;
class ITypeConstraintExpr : public ITypeConstraint {
public:

	virtual ~ITypeConstraintExpr() { }

	virtual ITypeExpr *expr() const = 0;

};

}

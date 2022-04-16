/*
 * ITypeConstraintExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeConstraint.h"
#include "vsc/ITypeExpr.h"

namespace vsc {

class ITypeConstraintExpr : public ITypeConstraint {
public:

	virtual ~ITypeConstraintExpr() { }

	virtual ITypeExpr *expr() const = 0;

};

}

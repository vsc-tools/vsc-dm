/*
 * ITypeExprVal.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeExpr.h"
#include "vsc/IModelVal.h"

namespace vsc {

class ITypeExprVal : public ITypeExpr {
public:

	virtual ~ITypeExprVal() { }

	virtual IModelVal *val() = 0;

};

}

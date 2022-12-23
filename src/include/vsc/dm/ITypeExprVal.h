/*
 * ITypeExprVal.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExpr.h"
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class ITypeExprVal : public ITypeExpr {
public:

	virtual ~ITypeExprVal() { }

	virtual IModelVal *val() = 0;

};

}
}

/*
 * IModelExprIn.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprIn;
using IModelExprInUP=UP<IModelExprIn>;
class IModelExprIn : public IModelExpr {
public:

	virtual ~IModelExprIn() { }

	virtual IModelExpr *lhs() const = 0;

	virtual IModelExprRangelist *rangelist() const = 0;

};

}
}

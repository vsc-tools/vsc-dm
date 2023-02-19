/*
 * IModelExprRange.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprRange;
using IModelExprRangeUP=UP<IModelExprRange>;
class IModelExprRange : public IModelExpr {
public:

	virtual ~IModelExprRange() { }

	virtual bool isSingle() const = 0;

	virtual IModelExpr *lower() const = 0;

	virtual IModelExpr *upper() const = 0;

};

}
}

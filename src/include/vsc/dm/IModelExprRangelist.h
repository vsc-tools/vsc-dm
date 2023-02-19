/*
 * IModelExprRangelist.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/IModelExprRange.h"

namespace vsc {
namespace dm {

class IModelExprRangelist;
using IModelExprRangelistUP=UP<IModelExprRangelist>;
class IModelExprRangelist : public IModelExpr {
public:

	virtual ~IModelExprRangelist() { }

	virtual const std::vector<IModelExprRangeUP> &ranges() const = 0;

	virtual const std::vector<IModelExprRangeUP> &getRanges() const = 0;

	virtual void addRange(IModelExprRange *range) = 0;

};

}
}


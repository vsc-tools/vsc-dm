/*
 * IModelExprRangelist.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"
#include "vsc/IModelExprRange.h"

namespace vsc {

class IModelExprRangelist;
using IModelExprRangelistUP=std::unique_ptr<IModelExprRangelist>;
class IModelExprRangelist : public IModelExpr {
public:

	virtual ~IModelExprRangelist() { }

	virtual const std::vector<IModelExprRangeUP> &ranges() const = 0;

	virtual const std::vector<IModelExprRangeUP> &getRanges() const = 0;

	virtual void addRange(IModelExprRange *range) = 0;

};

}


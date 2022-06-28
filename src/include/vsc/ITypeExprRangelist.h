/*
 * ITypeExprRangelist.h
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/ITypeExpr.h"
#include "vsc/ITypeExprRange.h"

namespace vsc {

class ITypeExprRangelist;
using ITypeExprRangelistUP=std::unique_ptr<ITypeExprRangelist>;
class ITypeExprRangelist : public ITypeExpr {
public:

	virtual ~ITypeExprRangelist() { }

	virtual const std::vector<ITypeExprRangeUP> &getRanges() const = 0;

	virtual void addRange(ITypeExprRange *rng) = 0;

};

}

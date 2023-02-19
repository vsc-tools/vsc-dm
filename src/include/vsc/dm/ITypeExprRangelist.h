/*
 * ITypeExprRangelist.h
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/dm/ITypeExpr.h"
#include "vsc/dm/ITypeExprRange.h"

namespace vsc {
namespace dm {

class ITypeExprRangelist;
using ITypeExprRangelistUP=UP<ITypeExprRangelist>;
class ITypeExprRangelist : public ITypeExpr {
public:

	virtual ~ITypeExprRangelist() { }

	virtual const std::vector<ITypeExprRangeUP> &getRanges() const = 0;

	virtual void addRange(ITypeExprRange *rng) = 0;

};

}
}

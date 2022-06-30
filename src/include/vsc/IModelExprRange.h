/*
 * IModelExprRange.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelExprRange;
using IModelExprRangeUP=std::unique_ptr<IModelExprRange>;
class IModelExprRange : public IModelExpr {
public:

	virtual ~IModelExprRange() { }

	virtual bool isSingle() const = 0;

	virtual IModelExpr *lower() const = 0;

	virtual IModelExpr *upper() const = 0;

};

}

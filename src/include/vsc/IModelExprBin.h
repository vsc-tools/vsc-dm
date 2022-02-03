/*
 * IModelExprBin.h
 *
 *  Created on: Feb 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/BinOp.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelExprBin : public IModelExpr {
public:

	virtual ~IModelExprBin() { }

	virtual int32_t width() const = 0;

	virtual IModelExpr *lhs() const = 0;

	virtual BinOp op() const = 0;

	virtual IModelExpr *rhs() const = 0;
};

}

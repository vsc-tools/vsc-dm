/*
 * IModelExprBin.h
 *
 *  Created on: Feb 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/BinOp.h"
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprBin : public IModelExpr {
public:

	virtual ~IModelExprBin() { }

	virtual int32_t width() = 0;

	virtual IModelExpr *lhs() const = 0;

	virtual BinOp op() const = 0;

	virtual IModelExpr *rhs() const = 0;
};

}
}

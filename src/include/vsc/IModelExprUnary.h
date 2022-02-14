/*
 * IModelExprUnary.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"
#include "vsc/UnaryOp.h"

namespace vsc {

class IModelExprUnary : public IModelExpr {
public:
	virtual ~IModelExprUnary() { }

	virtual IModelExpr *expr() const = 0;

	virtual UnaryOp op() const = 0;

};

}

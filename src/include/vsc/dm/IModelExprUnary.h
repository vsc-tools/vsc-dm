/*
 * IModelExprUnary.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/UnaryOp.h"

namespace vsc {
namespace dm {

class IModelExprUnary : public IModelExpr {
public:
	virtual ~IModelExprUnary() { }

	virtual IModelExpr *expr() const = 0;

	virtual UnaryOp op() const = 0;

};

}
}

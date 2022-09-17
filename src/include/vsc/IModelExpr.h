/*
 * IModelExpr.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include "vsc/IAccept.h"
#include "vsc/IModelVal.h"

namespace vsc {

class IModelExpr;
using IModelExprUP=std::unique_ptr<IModelExpr>;
class IModelExpr : public IAccept {
public:
	virtual ~IModelExpr() { }

	virtual int32_t width() = 0;


	/**
	 * Evaluate the expression and return a result
	 */
	virtual void eval(IModelVal *dst) = 0;
};

}

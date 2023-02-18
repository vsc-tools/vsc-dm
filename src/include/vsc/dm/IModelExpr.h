/*
 * IModelExpr.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class IModelExpr;
using IModelExprUP=vsc::dm::UP<IModelExpr>;
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
}

/*
 * IModelExprVal.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class IModelExprVal : public IModelExpr {
public:

	virtual ~IModelExprVal() { }

	virtual int32_t width() = 0;

	virtual const IModelVal *val() const = 0;

	virtual IModelVal  *val() = 0;

};

}
}

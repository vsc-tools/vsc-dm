/*
 * IModelExprCond.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprCond : public IModelExpr {
public:

	virtual ~IModelExprCond() { }

	virtual IModelExpr *getCond() const = 0;

	virtual IModelExpr *getTrue() const = 0;

	virtual IModelExpr *getFalse() const = 0;

};

}
}

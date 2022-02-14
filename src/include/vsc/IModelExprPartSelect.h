/*
 * IModelExprPartSelect.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelExprPartSelect : public IModelExpr {
public:

	virtual ~IModelExprPartSelect() { }

	virtual IModelExpr *lhs() const = 0;

	virtual int32_t lower() const = 0;

	virtual int32_t upper() const = 0;

};


}

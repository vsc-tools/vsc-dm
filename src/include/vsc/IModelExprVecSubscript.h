/*
 * IModelExprVecSubscript.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once

#include "vsc/IModelExpr.h"

namespace vsc {

class IModelExprVecSubscript : public IModelExpr {
public:

	virtual ~IModelExprVecSubscript() { }

	virtual IModelExpr *expr() const = 0;

	virtual IModelExpr *subscript() const = 0;

};


}

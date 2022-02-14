/*
 * IModelExprRef.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelExprRef : public IModelExpr {
public:

	virtual ~IModelExprRef() { }

	virtual IModelExpr *expr() const = 0;

};


}

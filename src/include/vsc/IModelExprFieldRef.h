/*
 * IModelExprFieldRef.h
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelExprFieldRef : public IModelExpr {
public:

	virtual ~IModelExprFieldRef() { }

	virtual IModelField *field() const = 0;

};

}

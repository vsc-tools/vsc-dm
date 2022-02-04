/*
 * IModelExprIn.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelExprIn;
using IModelExprInUP=std::unique_ptr<IModelExprIn>;
class IModelExprIn : public IModelExpr {
public:

	virtual ~IModelExprIn() { }

};

}

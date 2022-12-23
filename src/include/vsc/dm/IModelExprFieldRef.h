/*
 * IModelExprFieldRef.h
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprFieldRef : public IModelExpr {
public:

	virtual ~IModelExprFieldRef() { }

	virtual IModelField *field() const = 0;

};

}
}

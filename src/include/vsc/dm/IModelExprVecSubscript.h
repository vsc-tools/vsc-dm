/*
 * IModelExprVecSubscript.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once

#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprVecSubscript : public IModelExpr {
public:

	virtual ~IModelExprVecSubscript() { }

	virtual IModelExpr *expr() const = 0;

	virtual IModelExpr *subscript() const = 0;

};

}
}

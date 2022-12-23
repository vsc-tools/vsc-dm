/*
 * IModelExprPartSelect.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprPartSelect : public IModelExpr {
public:

	virtual ~IModelExprPartSelect() { }

	virtual IModelExpr *lhs() const = 0;

	virtual int32_t lower() const = 0;

	virtual int32_t upper() const = 0;

};


}
}

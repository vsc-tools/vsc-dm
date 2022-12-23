/*
 * IModelExprRef.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

class IModelExprRef : public virtual IModelExpr {
public:

	virtual ~IModelExprRef() { }

	virtual IModelExpr *expr() const = 0;

};

}
}

/*
 * ITypeExprVal.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IDataType.h"
#include "vsc/dm/ITypeExpr.h"
#include "vsc/dm/IModelVal.h"
#include "vsc/dm/Val.h"

namespace vsc {
namespace dm {

class ValRef;

class ITypeExprVal : public ITypeExpr {
public:

	virtual ~ITypeExprVal() { }

	virtual const ValRef &val() const = 0;

    virtual IDataType *type() const = 0;

};

}
}

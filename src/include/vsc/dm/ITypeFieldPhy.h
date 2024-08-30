/*
 * ITypeFieldPhy.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExpr.h"
#include "vsc/dm/ITypeField.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {

class ITypeFieldPhy : public virtual ITypeField {
public:

	virtual ~ITypeFieldPhy() { }

	virtual ITypeExpr *getInit() = 0;

};

}
}


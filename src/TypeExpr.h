/*
 * TypeExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeExpr.h"

namespace vsc {

class TypeExpr : public virtual ITypeExpr {
public:
	TypeExpr();

	virtual ~TypeExpr();

};

} /* namespace vsc */


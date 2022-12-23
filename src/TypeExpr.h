/*
 * TypeExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class TypeExpr : public virtual ITypeExpr {
public:
	TypeExpr();

	virtual ~TypeExpr();

};

}
} /* namespace vsc */


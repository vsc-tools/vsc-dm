/*
 * ITypeExprBin.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/BinOp.h"
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class ITypeExprBin;
using ITypeExprBinUP=UP<ITypeExprBin>;
class ITypeExprBin : public ITypeExpr {
public:
	virtual ~ITypeExprBin() { }

	virtual ITypeExpr *lhs() const = 0;

	virtual BinOp op() const = 0;

	virtual ITypeExpr *rhs() const = 0;

};

}
}

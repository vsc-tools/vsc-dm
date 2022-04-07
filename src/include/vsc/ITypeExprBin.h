/*
 * ITypeExprBin.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/BinOp.h"
#include "vsc/ITypeExpr.h"

namespace vsc {

class ITypeExprBin;
using ITypeExprBinUP=std::unique_ptr<ITypeExprBin>;
class ITypeExprBin : public ITypeExpr {
public:
	virtual ~ITypeExprBin() { }

	virtual ITypeExpr *lhs() const = 0;

	virtual BinOp op() const = 0;

	virtual ITypeExpr *rhs() const = 0;

};

}

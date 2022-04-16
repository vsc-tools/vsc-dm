/*
 * ITypeExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IAccept.h"

namespace vsc {

class ITypeExpr;
using ITypeExprUP=std::unique_ptr<ITypeExpr>;
class ITypeExpr : public IAccept {
public:

	virtual ~ITypeExpr() { }

};

}

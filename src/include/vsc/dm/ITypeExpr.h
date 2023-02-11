/*
 * ITypeExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IAccept.h"

namespace vsc {
namespace dm {

class ITypeExpr;
using ITypeExprUP=UP<ITypeExpr>;
class ITypeExpr : public IAccept {
public:

	virtual ~ITypeExpr() { }

};

}
}

/*
 * ITypeExprRange.h
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {

class ITypeExprRange;
using ITypeExprRangeUP=UP<ITypeExprRange>;
class ITypeExprRange : public ITypeExpr {
public:

	virtual ~ITypeExprRange() { }

	/**
	 * Indicates that this is a single-value
	 * range. If true, then only 'lower'  will
	 * hold a value.
	 */
	virtual bool isSingle() const = 0;

	virtual ITypeExpr *lower() const = 0;

	virtual ITypeExpr *upper() const = 0;
};

}
}

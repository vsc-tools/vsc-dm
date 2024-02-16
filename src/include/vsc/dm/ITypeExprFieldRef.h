/*
 * ITypeExprFieldRef.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/dm/ITypeExpr.h"

namespace vsc {
namespace dm {


class ITypeExprFieldRef;
using ITypeExprFieldRefUP=UP<ITypeExprFieldRef>;
class ITypeExprFieldRef : public ITypeExpr {
public:
enum class RootRefKind {
	TopDownScope,
	BottomUpScope,
    RootExpr
};

public:

	virtual ~ITypeExprFieldRef() { }

	virtual RootRefKind getRootRefKind() const = 0;

    virtual int32_t getRootRefOffset() const = 0;

    virtual int32_t getSubFieldIndex() const = 0;

};

}
}

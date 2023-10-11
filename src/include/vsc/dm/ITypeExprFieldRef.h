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

    virtual ITypeExpr *getRootExpr() const = 0;

	virtual RootRefKind getRootRefKind() const = 0;

    virtual int32_t getRootRefOffset() const = 0;

	virtual void addPathElem(int32_t idx) = 0;

	virtual uint32_t size() const = 0;

	virtual int32_t at(int32_t idx) const = 0;

	virtual const std::vector<int32_t> &getPath() const = 0;

};

}
}

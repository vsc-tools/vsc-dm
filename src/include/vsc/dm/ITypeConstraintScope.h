/*
 * ITypeConstraintScope.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/dm/ITypeConstraint.h"

namespace vsc {
namespace dm {

class ITypeConstraintScope;
using ITypeConstraintScopeUP=std::unique_ptr<ITypeConstraintScope>;
class ITypeConstraintScope : public ITypeConstraint {
public:

	virtual ~ITypeConstraintScope() { }

	virtual void addConstraint(ITypeConstraint *c) = 0;

	virtual const std::vector<ITypeConstraintUP> &constraints() const = 0;

};

}
}

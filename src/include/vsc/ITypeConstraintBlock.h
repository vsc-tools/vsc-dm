/*
 * ITypeConstraintBlock.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/ITypeConstraintScope.h"


namespace vsc {
class ITypeConstraintBlock : public ITypeConstraintScope {
public:

	virtual ~ITypeConstraintBlock() { }

	virtual const std::string &name() const = 0;

};

}

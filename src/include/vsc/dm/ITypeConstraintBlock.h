/*
 * ITypeConstraintBlock.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include <vector>
#include "vsc/dm/ITypeConstraintScope.h"


namespace vsc {
namespace dm {
class ITypeConstraintBlock : public ITypeConstraintScope {
public:

	virtual ~ITypeConstraintBlock() { }

	virtual const std::string &name() const = 0;

};

}
}

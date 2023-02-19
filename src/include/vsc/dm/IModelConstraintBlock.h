/*
 * IModelConstraintBlock.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelConstraintScope.h"

namespace vsc {
namespace dm {

class IModelConstraintBlock;
using IModelConstraintBlockUP=UP<IModelConstraintBlock>;
class IModelConstraintBlock : public virtual IModelConstraintScope {
public:

	virtual ~IModelConstraintBlock() { }

	virtual const std::string &name() const = 0;

};

}
}

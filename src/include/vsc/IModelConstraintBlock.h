/*
 * IModelConstraintBlock.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraintScope.h"

namespace vsc {

class IModelConstraintBlock;
using IModelConstraintBlockUP=std::unique_ptr<IModelConstraintBlock>;
class IModelConstraintBlock : public IModelConstraintScope {
public:

	virtual ~IModelConstraintBlock() { }

	virtual const std::string &name() const = 0;

};

}

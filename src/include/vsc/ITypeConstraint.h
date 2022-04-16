/*
 * ITypeConstraint.h
 *
 *  Created on: Apr 5, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IAccept.h"

namespace vsc {

class ITypeConstraint;
using ITypeConstraintUP=std::unique_ptr<ITypeConstraint>;
class ITypeConstraint : public IAccept {
public:
	virtual ~ITypeConstraint() { }

};

}

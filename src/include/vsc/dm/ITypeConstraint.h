/*
 * ITypeConstraint.h
 *
 *  Created on: Apr 5, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IAccept.h"

namespace vsc {
namespace dm {

class ITypeConstraint;
using ITypeConstraintUP=UP<ITypeConstraint>;
class ITypeConstraint : public IAccept {
public:
	virtual ~ITypeConstraint() { }

};

}
}

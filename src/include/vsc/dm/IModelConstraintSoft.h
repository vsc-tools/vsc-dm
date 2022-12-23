/*
 * IModelConstraintSoft.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelConstraint.h"
#include "vsc/dm/IModelConstraintExpr.h"

namespace vsc {
namespace dm {

class IModelConstraintSoft : public virtual IModelConstraint {
public:

	virtual ~IModelConstraintSoft() { }

	virtual IModelConstraintExpr *constraint() const = 0;

	virtual int32_t getPriority() const = 0;

};

}
}


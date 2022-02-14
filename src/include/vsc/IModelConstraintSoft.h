/*
 * IModelConstraintSoft.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraint.h"
#include "vsc/IModelConstraintExpr.h"

namespace vsc {

class IModelConstraintSoft : public IModelConstraint {
public:

	virtual ~IModelConstraintSoft() { }

	virtual IModelConstraintExpr *constraint() const = 0;

};


}


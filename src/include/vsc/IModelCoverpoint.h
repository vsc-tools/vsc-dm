/*
 * IModelCoverpoint.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include "vsc/IAccept.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelCoverpoint : public IAccept {
public:

	virtual ~IModelCoverpoint() { }

	virtual IModelExpr *target() const = 0;

	virtual const std::string &name() const = 0;

	virtual IModelExpr *iff() const = 0;

};

}


/*
 * ModelConstraintForeach.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraintForeach.h"

namespace vsc {

class ModelConstraintForeach : public IModelConstraintForeach {
public:
	ModelConstraintForeach();
//			IModelExpr			*);

	virtual ~ModelConstraintForeach();
};

} /* namespace vsc */


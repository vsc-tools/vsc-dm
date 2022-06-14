/*
 * IModelBuildContext.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"
#include "vsc/IModelField.h"

namespace vsc {

class IModelBuildContext {
public:
	virtual ~IModelBuildContext() { }

	virtual IContext *ctxt() const = 0;

	virtual void pushField(IModelField *f) = 0;

	virtual void popField() = 0;

	virtual IModelField *getField(int32_t offset=0) = 0;

};

}


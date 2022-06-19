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

	virtual int32_t fieldStackSize() = 0;

	virtual IModelField *getField(int32_t offset) = 0;

	template <class T> T *getFieldT(int32_t offset) {
		return dynamic_cast<T *>(getField(offset));
	}

};

}


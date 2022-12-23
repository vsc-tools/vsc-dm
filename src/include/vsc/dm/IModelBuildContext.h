/*
 * IModelBuildContext.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 */

#pragma once
#include <stdint.h>

namespace vsc {
namespace dm {

class IContext;
class IModelField;

class IModelBuildContext {
public:
	virtual ~IModelBuildContext() { }

	virtual IContext *ctxt() const = 0;

	virtual void pushTopDownScope(IModelField *f) = 0;

	virtual IModelField *getTopDownScope() const = 0;

	template <class T> T *getTopDownScopeT() {
		return dynamic_cast<T *>(getTopDownScope());
	}

	virtual void popTopDownScope() = 0;

	virtual void pushBottomUpScope(IModelField *f) = 0;

	virtual IModelField *getBottomUpScope(int32_t offset=-1) const = 0;

	template <class T> T *getBottomUpScopeT(int32_t offset=-1) {
		return dynamic_cast<T *>(getBottomUpScope(offset));
	}

	virtual void popBottomUpScope() = 0;

	virtual IModelField *getScope() const = 0;

	template <class T> T *getScopeT() const {
		return dynamic_cast<T *>(getScope());
	}

};

}
}


/*
 * ITypeField.h
 *
 *  Created on: Apr 5, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include "vsc/IAccept.h"
#include "vsc/IDataType.h"
#include "vsc/TypeFieldAttr.h"
#include "vsc/IModelVal.h"
#include "vsc/IModelBuildContext.h"

namespace vsc {

class IDataTypeStruct;

class ITypeField;
using ITypeFieldUP=std::unique_ptr<ITypeField>;
class ITypeField : public IAccept {
public:

	virtual ~ITypeField() { }

	virtual ITypeField *getParent() const = 0;

	virtual void setParent(ITypeField *p) = 0;

	virtual int32_t getIndex() const = 0;

	virtual void setIndex(int32_t) = 0;

	virtual const std::string &name() const = 0;

	virtual IDataType *getDataType() const = 0;

	template <class T> T *getDataTypeT() const {
		return dynamic_cast<T *>(getDataType());
	}

	virtual void setDataType(IDataType *t, bool owned=false) = 0;

	virtual ITypeField *getField(int32_t idx) const = 0;

	virtual TypeFieldAttr getAttr() const = 0;

	virtual IModelField *mkModelField(
		IModelBuildContext 			*ctxt) = 0;

	template <class T> T *mkModelFieldT(
		IModelBuildContext 			*ctxt) {
		return dynamic_cast<T *>(mkModelField(ctxt));
	}

};

}

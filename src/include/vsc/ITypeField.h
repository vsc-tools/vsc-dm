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

namespace vsc {

class IDataTypeStruct;

class ITypeField;
using ITypeFieldUP=std::unique_ptr<ITypeField>;
class ITypeField : public IAccept {
public:

	virtual ~ITypeField() { }

	virtual IDataTypeStruct *getParent() = 0;

	virtual void setParent(IDataTypeStruct *p) = 0;

	virtual const std::string &name() const = 0;

	virtual IDataType *getDataType() const = 0;

	virtual TypeFieldAttr getAttr() const = 0;

	virtual IModelVal *getInit() const = 0;


};

}
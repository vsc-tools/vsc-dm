/*
 * ITypeFieldRef.h
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include "vsc/IAccept.h"
#include "vsc/IDataType.h"
#include "vsc/TypeFieldAttr.h"

namespace vsc {

class ITypeFieldRef : public IAccept {
public:

	virtual ~ITypeFieldRef() { }

	virtual IDataTypeStruct *getParent() = 0;

	virtual void setParent(IDataTypeStruct *p) = 0;

	virtual const std::string &name() const = 0;

	virtual IDataType *getDataType() const = 0;

	virtual TypeFieldAttr getAttr() const = 0;


};

}


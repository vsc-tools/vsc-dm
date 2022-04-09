/*
 * IModelFieldRoot.h
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataType.h"
#include "vsc/IModelField.h"

namespace vsc {

class IModelFieldRoot : public IModelField {
public:

	virtual ~IModelFieldRoot() { }

	virtual const std::string &name() const = 0;

	virtual IDataType *getDataType() const = 0;

};
}

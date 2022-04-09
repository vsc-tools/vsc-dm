/*
 * IModelFieldType.h
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"

namespace vsc {

class IModelFieldType : public IModelField {
public:

	virtual ~IModelFieldType() { }

	virtual const std::string &name() const = 0;

};


}

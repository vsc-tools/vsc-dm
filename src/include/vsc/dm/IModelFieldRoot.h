/*
 * IModelFieldRoot.h
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelField.h"

namespace vsc {
namespace dm {

/**
 * Represents a field characterized by a datatype
 * and name. No type information (eg declaration location)
 * is available for the field itself.
 */
class IModelFieldRoot : public virtual IModelField {
public:

	virtual ~IModelFieldRoot() { }

	virtual const std::string &name() const = 0;

	virtual void setName(const std::string &n) = 0;

	virtual IDataType *getDataType() const = 0;

};

}
}

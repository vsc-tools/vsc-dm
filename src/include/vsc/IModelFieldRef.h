/*
 * IModelFieldRef.h
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"

namespace vsc {

class IModelFieldRef : public IModelField {
public:

	virtual ~IModelFieldRef() { }

	virtual void setRef(IModelField *ref) = 0;

	virtual IModelField *getRef() const = 0;

};

}

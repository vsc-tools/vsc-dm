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

	virtual ITypeField *getTypeField() const = 0;

	template <class T> T *getTypeFieldT() const {
		return dynamic_cast<T *>(getTypeField());
	}

};


}

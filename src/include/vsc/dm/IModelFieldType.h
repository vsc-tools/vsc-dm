/*
 * IModelFieldType.h
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelField.h"

namespace vsc {
namespace dm {

class IModelFieldType : public IModelField {
public:

	virtual ~IModelFieldType() { }

	virtual ITypeField *getTypeField() const = 0;

	template <class T> T *getTypeFieldT() const {
		return dynamic_cast<T *>(getTypeField());
	}

};

}
}

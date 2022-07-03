/*
 * ITypeFieldVec.h
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"

namespace vsc {

class ITypeFieldVec : public virtual ITypeField {
public:

	virtual ~ITypeFieldVec() { }

	virtual ITypeField *getSizeRef() const = 0;

	virtual IModelVal *getInitSize() const = 0;

};

}

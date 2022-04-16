/*
 * IModelFieldVec.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"

namespace vsc {

class IModelFieldVec : public IModelField {
public:

	virtual ~IModelFieldVec() { }

	virtual IModelField *size() const = 0;

	virtual void size(IModelField *f) = 0;

	virtual void push_back(IModelField *f) = 0;

	virtual void pop_back() = 0;

};

}

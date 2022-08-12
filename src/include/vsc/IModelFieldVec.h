/*
 * IModelFieldVec.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IModelField.h"
#include "vsc/IModelFieldFactory.h"

namespace vsc {

class IModelFieldVec;
using IModelFieldVecUP=std::unique_ptr<IModelFieldVec>;
class IModelFieldVec : public virtual IModelField {
public:

	virtual ~IModelFieldVec() { }

	/**
	 * Returns a handle to the size property
	 */
	virtual IModelField *getSizeRef() const = 0;

	/*
	 * Returns the number of elements currently in the vector
	 */
	virtual uint32_t getSize() const = 0;

	virtual void push_back(IModelField *f) = 0;

	virtual IModelField *at(uint32_t idx) = 0;

	virtual void pop_back() = 0;

	virtual IModelFieldFactory *getFieldFactory() = 0;

	virtual void setFieldFactory(IModelFieldFactory *) = 0;

};

}

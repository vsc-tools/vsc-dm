/*
 * IModelFieldVec.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IModelField.h"
#include "vsc/dm/IModelFieldVecElemFactory.h"

namespace vsc {
namespace dm {

class IModelFieldVec;
using IModelFieldVecUP=UP<IModelFieldVec>;
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

	virtual IModelFieldVecElemFactory *getElemFactory() = 0;

	virtual void setElemFactory(IModelFieldVecElemFactory *) = 0;

};

}
}

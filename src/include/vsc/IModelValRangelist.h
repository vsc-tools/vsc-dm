/*
 * IModelValRangelist.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelVal.h"
#include "vsc/IModelValRange.h"

namespace vsc {

class IModelValRangelist {
public:

	virtual ~IModelValRangelist() { }

	virtual bool getIsSigned() const = 0;

	virtual void setIsSigned(bool s) = 0;

	virtual void push_back(const IModelValRange *v) = 0;

	virtual void push_back(const IModelValRange &v) = 0;

	virtual void clear() = 0;

	virtual uint32_t size() const = 0;

	virtual const IModelValRange *at(uint32_t i) const = 0;

	virtual IModelValRange *at(uint32_t i) = 0;

};

}

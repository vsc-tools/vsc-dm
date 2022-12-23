/*
 * IModelValRange.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class IModelValRange {
public:

	virtual ~IModelValRange() { }

	virtual IModelVal *lower() = 0;

	virtual const IModelVal *lower() const = 0;

	virtual IModelVal *upper() = 0;

	virtual const IModelVal *upper() const = 0;

};

}
}

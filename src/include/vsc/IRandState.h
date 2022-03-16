/*
 * IRandState.h
 *
 *  Created on: Mar 15, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include "vsc/IModelVal.h"

namespace vsc {

class IRandState;
using IRandStateUP=std::unique_ptr<IRandState>;
class IRandState {
public:

	virtual ~IRandState() { }

	virtual int32_t randint32(
			int32_t		min,
			int32_t		max) = 0;

	virtual void randbits(IModelVal *val) = 0;

};

}

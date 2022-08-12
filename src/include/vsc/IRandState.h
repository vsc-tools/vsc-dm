/*
 * IRandState.h
 *
 *  Created on: Mar 15, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include <stdint.h>
#include "vsc/IModelVal.h"

namespace vsc {

class IRandState;
using IRandStateUP=std::unique_ptr<IRandState>;
class IRandState {
public:

	virtual ~IRandState() { }

	virtual const std::string &seed() const = 0;

	virtual int32_t randint32(
			int32_t		min,
			int32_t		max) = 0;

	virtual uint64_t rand_ui64() = 0;

	virtual int64_t rand_i64() = 0;

	virtual void randbits(IModelVal *val) = 0;

	virtual void setState(IRandState *other) = 0;

	virtual IRandState *clone() = 0;

};

}

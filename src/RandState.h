/*
 * RandState.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include <random>
#include <stdint.h>
#include "vsc/IRandState.h"
#include "ModelVal.h"

namespace vsc {

class RandState;
using RandStateUP=std::unique_ptr<RandState>;
class RandState : public IRandState {
public:
	RandState(uint32_t seed);

	virtual ~RandState();

	virtual int32_t randint32(
			int32_t		min,
			int32_t		max) override;

	/**
	 * Fills the value with a random bit pattern
	 */
	virtual void randbits(IModelVal *val) override;

protected:
	uint64_t next();

private:
	std::mt19937_64 	m_state;

};

} /* namespace vsc */


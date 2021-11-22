/*
 * RandState.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include <random>
#include <stdint.h>
#include "ModelVal.h"

namespace vsc {

class RandState;
using RandStateUP=std::unique_ptr<RandState>;
class RandState {
public:
	RandState(uint32_t seed);

	virtual ~RandState();

	int32_t randint32(
			int32_t		min,
			int32_t		max);

	/**
	 * Fills the value with a random bit pattern
	 */
	void randbits(ModelVal &val);

protected:
	uint64_t next();

private:
	std::mt19937_64 	m_state;

};

} /* namespace vsc */


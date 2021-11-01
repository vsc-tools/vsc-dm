/*
 * RandState.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include "ModelVal.h"

namespace vsc {

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
	uint64_t			m_state;

};

} /* namespace vsc */


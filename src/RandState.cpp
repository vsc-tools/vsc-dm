/*
 * RandState.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#include "RandState.h"

namespace vsc {

RandState::RandState(uint32_t seed) {
	m_state = (0x330EULL << 32)
			| ((uint64_t)(seed & 0xFFFF) << 16)
			| (seed >> 16);
}

RandState::~RandState() {
	// TODO Auto-generated destructor stub
}

int32_t RandState::randint32(
			int32_t		min,
			int32_t		max) {
	uint64_t next_v = next();
	;
}

void RandState::randbits(ModelVal &val) {
	;
}

uint64_t RandState::next() {
	m_state ^= (m_state >> 12);
	m_state ^= (m_state << 25);
	m_state ^= (m_state >> 27);

	return (m_state * 0x2545F4914F6DD1DULL);
}

} /* namespace vsc */

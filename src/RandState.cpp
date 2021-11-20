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
	if (min == max) {
		return min;
	} else {
		next_v = (next_v % (max-min+1)) + min;
		return next_v;
	}
}

void RandState::randbits(ModelVal &val) {
	if (val.bits() <= 64) {
		val.u64(next());
	} else {
		uint32_t n_words = (val.bits()-1)/64+1;
		for (uint32_t i=0; i<n_words; i++) {
			uint64_t rv = next();
#ifdef UNDEFINED
		val.set_word(i, rv);

		if (i+1 < n_words) {
			i++;
			val.set_word(i, rv >> 32);
		}

		if (i+1 == n_words && (val.bits()%32) != 0) {
			// Mask the last word
			val.set_word(i,
					(val.get_word(i) & (1 << (val.bits()%32))-1));
		}
#endif
		}
	}
}

uint64_t RandState::next() {
	/*
	m_state ^= (m_state >> 12);
	m_state ^= (m_state << 25);
	m_state ^= (m_state >> 27);

	return (m_state * 0x2545F4914F6DD1DULL);
    val = self.state
    val ^= val << 13
    val ^= val >> 7
    val ^= val << 17
	 */

	m_state ^= (m_state << 13);
    m_state ^= (m_state >> 7);
    m_state ^= (m_state << 17);

    return m_state;
}

} /* namespace vsc */

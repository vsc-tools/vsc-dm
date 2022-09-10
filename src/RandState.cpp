/*
 * RandState.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#include <random>
#include "RandState.h"

namespace vsc {

RandState::RandState(const std::string &seed) : m_seed(seed) {
	std::seed_seq seq(seed.begin(), seed.end());
	m_state = std::mt19937_64(seq);
}

RandState::RandState(const std::mt19937_64 &state) : m_state(state) {

}

RandState::~RandState() {
	// TODO Auto-generated destructor stub
}

int32_t RandState::randint32(
			int32_t		min,
			int32_t		max) {
	uint64_t next_v = next_ui64();
	if (min == max) {
		return min;
	} else {
		next_v = (next_v % (max-min+1)) + min;
		return next_v;
	}
}

uint64_t RandState::rand_ui64() {
	return next_ui64();
}

int64_t RandState::rand_i64() {
	return static_cast<int64_t>(next_ui64());
}

void RandState::randbits(IModelVal *val) {
	if (val->bits() <= 64) {
		uint64_t bits = next_ui64();
		val->val_u(bits);
	} else {
		uint32_t n_words = (val->bits()-1)/64+1;
		for (uint32_t i=0; i<n_words; i++) {
			uint64_t rv = next_ui64();
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

uint64_t RandState::next_ui64() {
	uint64_t ret = m_state();
	return ret;
}

void RandState::setState(IRandState *other) {
	m_state = dynamic_cast<RandState *>(other)->m_state;
}

IRandState *RandState::clone() const {
	RandState *ret = new RandState(m_state);
	return ret;
}

IRandState *RandState::next() {
	m_state(); // Mutate state
	// Return a clone
	return new RandState(m_state);
}

} /* namespace vsc */

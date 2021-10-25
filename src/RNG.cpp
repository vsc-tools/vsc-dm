/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * RNG.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "RNG.h"
#include <stdlib.h>

namespace vsc {

RNG::RNG(uint32_t seed) {
	m_a = 0x5DEECE66DULL;
	m_c = 0xb;

	m_gen.seed(seed);

	m_next = (0x330EULL << 32)
			| ((uint64_t)(seed & 0xFFFF) << 16)
			| (seed >> 16);
//	m_next[0] = (seed >> 16);
//	m_next[1] = (seed & 0xFFFF);
//	m_next[2] = 0x330E;
}

RNG::~RNG() {
	// TODO Auto-generated destructor stub
}

uint32_t RNG::next() {
	uint64_t		X;
	uint64_t		tmp;

//	X = (((uint64_t)m_next[2] << 32) | ((uint32_t)m_next[1] << 16) | m_next[0]);
//	m_next = ((m_next * m_a + m_c) & 0xFFFFFFFFFFFF);
//	m_next = (m_next * m_a + m_c);
	m_next ^= (m_next >> 12);
	m_next ^= (m_next << 25);
	m_next ^= (m_next >> 27);



//	uint32_t ret = nrand48(xsubi);
//	return (m_next >> 16);
	return (m_next * 0x2545F4914F6DD1DULL);
//	return m_gen();
}

uint32_t RNG::randint_u(
			uint32_t	min,
			uint32_t	max) {
	uint32_t n = next();
	if (min!=max) {
		return (min + (n%(max-min+1)));
	} else {
		return min;
	}
}

} /* namespace vsc */

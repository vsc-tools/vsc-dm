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
 * ModelVal.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#include "ModelVal.h"
#include "DataTypeWidthVisitor.h"
#include <string.h>

namespace vsc {

ModelVal::ModelVal() : m_val{0}, m_bits(0) {
	// TODO Auto-generated constructor stub

}

ModelVal::ModelVal(int32_t bits) : m_val{0}, m_bits(bits) {
	if (bits > 64) {
		m_val.vp = new uint64_t[((bits-1)/64)+1];
		memset(m_val.vp, 0, sizeof(uint64_t)*(((bits-1)/64)+1));
	}
}

ModelVal::ModelVal(const ModelVal &rhs) {
	m_bits = rhs.m_bits;

	if (m_bits <= 64) {
		m_val.v = rhs.m_val.v;

		if (m_bits < 64) {
			m_val.v &= (1ULL << m_bits)-1;
		}
	} else {
		m_val.vp = new uint64_t[(m_bits-1)/64+1];
		memcpy(m_val.vp, rhs.m_val.vp, sizeof(uint64_t)*((m_bits-1)/64+1));
	}
}

void ModelVal::operator = (const ModelVal &rhs) {
	// Clean up first
	if (m_bits > 64 && m_val.vp) {
		delete [] m_val.vp;
	}

	m_bits = rhs.m_bits;

	if (m_bits <= 64) {
		m_val.v = rhs.m_val.v;

		if (m_bits < 64) {
			m_val.v &= ((1ULL << m_bits)-1);
		}
	} else {
		m_val.vp = new uint64_t[(m_bits-1)/64+1];
		memcpy(m_val.vp, rhs.m_val.vp, sizeof(uint64_t)*((m_bits-1)/64+1));
	}
}

ModelVal::~ModelVal() {
	if (m_bits > 64 && m_val.vp) {
		delete [] m_val.vp;
	}
}

void ModelVal::bits(uint32_t b) {
	// TODO: handle transitions between val and vec
	if ((m_bits <= 64) != (b <= 64)) {
		// I

	}
	m_bits = b;
}

uint32_t ModelVal::u32() const {
	if (m_bits <= 64) {
		return m_val.v;
	} else {
		return m_val.vp[0];
	}
}

void ModelVal::u32(uint32_t v) {
	if (m_bits <= 64) {
		if (m_bits < 32) {
			v &= (1ULL << m_bits)-1;
		}
		m_val.v = v;
	} else {
		m_val.vp[0] = v;
		for (uint32_t i=1; i<((m_bits-1)/64)+1; i++) {
			m_val.vp[i] = 0;
		}
	}
}

int32_t ModelVal::i32() const {
#ifdef UNDEFINED
	uint32_t val = m_val[0];

	if (m_bits < 32) {
		val &= ((1ULL << m_bits)-1);

		// Handle signing for smaller values
		if (val & (1 << (m_bits-1))) {
			val = (~val+1);
		}
	}

	return val;
#endif
}

uint64_t ModelVal::u64() const {
	if (m_bits < 64) {
		return m_val.v;
	} else {
		return m_val.vp[0];
	}
}

void ModelVal::u64(uint64_t v) {
	if (m_bits <= 64) {
		if (m_bits < 64) {
			v &= (1ULL << m_bits)-1;
		}
		m_val.v = v;
	} else {
		uint32_t n_words = (m_bits-1)/64+1;
		m_val.vp[0] = v;
		for (uint32_t i=1; i<n_words; i++) {
			m_val.vp[i] = 0;
		}

		if (m_bits%64) {
			// Must mask last word
			m_val.vp[n_words-1] &= (1ULL << (m_bits%64))-1;
		}
	}
}

int64_t ModelVal::i64() const {
#ifdef UNDEFINED
	uint64_t val = 0;

	if (m_val.size() >= 2) {
		val = m_val[1];
		val <<= 32;
	}
	val |= m_val[0];

	if (m_bits < 64) {
		val &= ((1ULL << m_bits)-1);

		// Handle signing for smaller values
		if (val & (1 << (m_bits-1))) {
			val = (~val+1);
		}
	}

	return val;
#endif
}


#ifdef UNDEFINED
uint32_t ModelVal::at(uint32_t b) const {
	uint32_t val = m_val.at(b/32);
	return ((val >> (b%32)) & 1);
}
#endif

void ModelVal::to_bits(char *bits) const {
#ifdef UNDEFINED
	if (m_bits <= 64) {
	} else {
	}
	char *ep = bits+m_bits;
	*ep-- = 0;

	uint32_t words=(m_bits-1)/32+1;
	for (uint32_t wi=0; wi<words; wi++) {
		uint32_t word = m_val[wi];
		for (uint32_t bi=0; bi<32 && ep >= bits; bi++) {
			*ep = '0'+(word&1);
			ep--;
			word >>= 1;
		}
	}
#endif
}

void ModelVal::from_bits(const char *bits, int32_t width) {
#ifdef UNDEFINED
	// Width is for the incoming bits. It often happens
	// that the width of the literal is wider than
	if (width == -1) {
		width = strlen(bits);
	}
	const char *ep = bits+width-1;
	uint32_t n_words = ((width-1)/32)+1;

	m_bits = width;
	while (m_val.size() < n_words) {
		m_val.push_back(0);
	}

	for (uint32_t wi=0; wi<n_words; wi++) {
		uint32_t word = 0;
		for (uint32_t bi=0; bi<32 && ep >= bits; bi++) {
			word |= (*ep - '0') << bi;
			ep--;
		}
		m_val[wi] = word;
	}
#endif
}

#ifdef UNDEFINED
void ModelVal::set_bit(uint32_t bit, uint32_t val) {
	uint32_t wi = bit/32;
	uint32_t bi = bit%32;
	m_val[wi] &= ~(1ULL << bi);
	m_val[wi] |= ((val&1) << bi);
}

uint32_t ModelVal::get_bit(uint32_t bit) {
	uint32_t wi = bit/32;
	uint32_t bi = bit%32;
	return (m_val[wi] & (1 << bi))?1:0;
}

void ModelVal::set_word(uint32_t wi, uint32_t val) {
	m_val[wi] = val;
}

void ModelVal::push_bit(uint32_t b) {
	uint32_t val_idx = (m_bits+1)/32;
	if (val_idx >= m_val.size()) {
		m_val.push_back(0);
	}
	m_val[val_idx] |= ((b&1) << (m_bits%32));
	m_bits++;
}

void ModelVal::push_word(uint32_t v) {
	if (!(m_bits%32)) {
		m_val.push_back(v);
		m_bits += 32;
	} else {
		for (uint32_t i=0; i<32; i++) {
			push_bit(v&1);
			v >>= 1;
		}
	}
}

void ModelVal::clear() {
	m_bits = 0;
}
#endif

#ifdef UNDEFINED
int64_t ModelVal::val_i() const {
	int64_t ret;
	if (m_bits > 64) {
		ret = m_val.vp[0];
	} else {
		ret = m_val.v;
		if (m_bits < 64) {
			// Sign-extend
			ret >>= (64-m_bits);
			ret <<= (64-m_bits);
		}
	}
	return ret;
}

uint64_t ModelVal::val_u() const {
	if (m_bits > 64) {
		return m_val.vp[0];
	} else {
		return m_val.v;
	}
}
#endif

void ModelVal::val_u(uint64_t v, int32_t width) {
	if (m_bits > 64) {
		m_val.vp[0] = v;
		if (width < 64) {
			m_val.vp[0] &= (1ULL << width)-1;
		}
	} else {
		m_val.v = v;
		if (width < 64) {
			m_val.v &= (1ULL << width)-1;
		}
	}
}

#ifdef UNDEFINED
ModelVal::iterator ModelVal::begin() {
	return ModelVal::iterator(this, 0);
}

ModelVal::iterator::iterator() : m_val(0), m_idx(-1) {

}

ModelVal::iterator::iterator(ModelVal *v, int32_t idx) :
		m_val(v), m_idx(idx) {

}

uint32_t ModelVal::iterator::get32() {
	uint32_t ret = 0;
	if (m_val && m_idx < m_val->bits()) {
		if (!(m_idx%32)) {
			ret = m_val->m_val[m_idx/32];
			m_idx += 32;
		} else {
			// TODO: handle unaligned access
		}
	}
	return ret;
}

void ModelVal::iterator::set32(uint32_t val) {
	if (m_val && m_idx < m_val->bits()) {
		if (!(m_idx%32)) {
			m_val->m_val[m_idx/32] = val;
			m_idx += 32;
		} else {
			// TODO: handle unaligned access
		}
	}
}

uint64_t ModelVal::iterator::get64() {
	;
}

void ModelVal::iterator::set64(uint64_t val) {
	;
}

ModelVal::const_iterator::const_iterator() : m_val(0), m_idx(-1) {

}

ModelVal::const_iterator::const_iterator(ModelVal *v, int32_t idx) :
		m_val(v), m_idx(idx) {

}
#endif

ModelVal ModelVal::slice(
			int32_t		upper,
			int32_t		lower) {
#ifdef UNDEFINED
	ModelVal ret((upper-lower+1));
	for (uint32_t bit=lower; bit<=upper; bit++) {
		ret.set_bit(bit-lower, get_bit(bit));
	}
	return ret;
#endif
}

} /* namespace vsc */

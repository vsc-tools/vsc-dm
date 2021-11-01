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
#include <string.h>

namespace vsc {

ModelVal::ModelVal() :
		m_type(0),
		m_val(0),
		m_is_signed(false),
		m_bits(0) {
	// TODO Auto-generated constructor stub

}

ModelVal::ModelVal(
			bool		is_signed,
			int32_t		bits) :
		m_type(0), m_is_signed(is_signed), m_bits(bits),
		m_val(0, ((bits-1)/32)+1) {

}

ModelVal::ModelVal(DataType *type) :
		m_type(type),
		m_val(0),
		m_is_signed(false),
		m_bits(0) {
	// TODO: determine signed/width from type

}

ModelVal::~ModelVal() {
	// TODO Auto-generated destructor stub
}

uint32_t ModelVal::u32() const {
	uint32_t val = m_val[0];

	if (m_bits < 32) {
		val &= ((1 << m_bits)-1);
	}

	return val;
}

int32_t ModelVal::i32() const {
	uint32_t val = m_val[0];

	if (m_bits < 32) {
		val &= ((1 << m_bits)-1);

		// Handle signing for smaller values
		if (val & (1 << (m_bits-1))) {
			val = (~val+1);
		}
	}

	return val;
}

uint64_t ModelVal::u64() const {
	uint64_t val = 0;

	if (m_val.size() >= 2) {
		val = m_val[1];
		val <<= 32;
	}
	val |= m_val[0];

	if (m_bits < 64) {
		val &= ((1ULL << m_bits)-1);
	}

	return val;
}

int64_t ModelVal::i64() const {
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
}


uint32_t ModelVal::at(uint32_t b) const {
	uint32_t val = m_val.at(b/32);
	return ((val >> (b%32)) & 1);
}

void ModelVal::to_bits(char *bits) const {
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
}

void ModelVal::from_bits(const char *bits, int32_t width) {
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

	/*
	fprintf(stdout, "from_bits: %s\n", bits);
	for (uint32_t i=0; i<m_val.size(); i++) {
		fprintf(stdout, "  val[%d]=0x%08x\n", i, m_val[i]);
	}
	 */
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

int64_t ModelVal::val_i() const {
	uint64_t val;
	if (m_val.size() >= 2) {
		val = m_val[1];
		val <<= 32;
		val |= m_val[0];
	} else {
		val = m_val[0];
	}
	return val;
}

uint64_t ModelVal::val_u() const {
	if (m_val.size() >= 2) {
		uint64_t val = m_val[1];
		val <<= 32;
		val |= m_val[0];
		return val;
	} else {
		return m_val[0];
	}
}

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

} /* namespace vsc */

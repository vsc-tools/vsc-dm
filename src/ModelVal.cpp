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

namespace vsc {

ModelVal::ModelVal() : m_type(0), m_val(0), m_bits(0) {
	// TODO Auto-generated constructor stub

}

ModelVal::ModelVal(DataType *type) : m_type(type), m_val(0), m_bits(0) {

}

ModelVal::~ModelVal() {
	// TODO Auto-generated destructor stub
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

void ModelVal::iterator::append(uint32_t val) {
	if (m_idx < m_val->m_val.size()) {
		m_val->m_val[m_idx] = val;
	} else {
		m_val->m_val.push_back(val);
	}
	m_idx++;
}

ModelVal::const_iterator::const_iterator() : m_val(0), m_idx(-1) {

}

ModelVal::const_iterator::const_iterator(ModelVal *v, int32_t idx) :
		m_val(v), m_idx(idx) {

}

} /* namespace vsc */

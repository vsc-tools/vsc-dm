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

ModelVal::ModelVal() : m_type(0), m_val(0) {
	// TODO Auto-generated constructor stub

}

ModelVal::ModelVal(DataType *type) : m_type(type), m_val(0) {

}

ModelVal::~ModelVal() {
	// TODO Auto-generated destructor stub
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

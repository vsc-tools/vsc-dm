/*
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

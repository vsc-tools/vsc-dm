/*
 * ModelFieldVec.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#include "ModelFieldVec.h"

namespace vsc {

ModelFieldVec::ModelFieldVec(ModelField *size) : m_size(size) {
	m_size->parent(this);
	m_size->set_flag(ModelFieldFlag_VecSize);
}

ModelFieldVec::~ModelFieldVec() {
	// TODO Auto-generated destructor stub
}

void ModelFieldVec::push_back(ModelField *f) {
	m_fields.push_back(ModelFieldUP(f));
	m_size->val()->val_u(m_fields.size());
}

void ModelFieldVec::pop_back() {
	m_fields.pop_back();
	m_size->val()->val_u(m_fields.size());
}

} /* namespace vsc */

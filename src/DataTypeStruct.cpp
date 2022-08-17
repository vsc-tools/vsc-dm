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
 * DataTypeStruct.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#include "DataTypeStruct.h"
#include "TypeField.h"
#include "TypeConstraint.h"
#include "vsc/impl/TaskBuildModelField.h"

namespace vsc {

DataTypeStruct::DataTypeStruct(const std::string &name) : 
	m_name(name), m_factory(new TaskBuildModelField()) {
	// TODO Auto-generated constructor stub

}

DataTypeStruct::~DataTypeStruct() {
	// TODO Auto-generated destructor stub
}

void DataTypeStruct::addField(ITypeField *f) {
	f->setIndex(m_fields.size());
	f->setParent(this);
	m_fields.push_back(ITypeFieldUP(f));
}

const std::vector<ITypeFieldUP> &DataTypeStruct::getFields() const {
	return m_fields;
}

ITypeField *DataTypeStruct::getField(int32_t idx) {
	if (idx < 0 || idx >= m_fields.size()) {
		return 0;
	} else {
		return m_fields.at(idx).get();
	}
}

void DataTypeStruct::addConstraint(ITypeConstraint *c) {
	m_constraints.push_back(ITypeConstraintUP(c));
}

const std::vector<ITypeConstraintUP> &DataTypeStruct::getConstraints() const {
	return m_constraints;
}

} /* namespace vsc */

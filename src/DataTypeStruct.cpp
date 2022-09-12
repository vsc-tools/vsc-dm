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

#include "vsc/impl/TaskIsTypeFieldRef.h"
#include "DataTypeStruct.h"
#include "TypeField.h"
#include "TypeConstraint.h"

namespace vsc {

DataTypeStruct::DataTypeStruct(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

DataTypeStruct::~DataTypeStruct() {
	// TODO Auto-generated destructor stub
}

void DataTypeStruct::addField(ITypeField *f) {
	f->setIndex(m_fields.size());
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

IModelField *DataTypeStruct::mkRootField(
	IModelBuildContext	*ctxt,
	const std::string	&name,
	bool				is_ref) {
	IModelField *ret;

	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name);

		// Need to build sub-fields and constraints
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

IModelField *DataTypeStruct::mkTypeField(
	IModelBuildContext	*ctxt,
	ITypeField			*type) {
	IModelField *ret;

	if (TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ret = ctxt->ctxt()->mkModelFieldType(type);
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

} /* namespace vsc */

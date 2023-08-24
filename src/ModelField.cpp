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
 * ModelField.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#include "ModelField.h"
#include "DataTypeWidthVisitor.h"

namespace vsc {
namespace dm {

ModelField::ModelField() : m_parent(0), m_flags(ModelFieldFlag::NoFlags) {
	// TODO Auto-generated constructor stub

}

ModelField::ModelField(IDataType *type) :
		m_parent(0) /*, m_val(32)*/, m_flags(ModelFieldFlag::NoFlags) {
    /*
	if (type) {
		m_val = ModelVal(DataTypeWidthVisitor().width(type).second);
	}
	// TODO: obtain actual width
	fprintf(stdout, "ModelField::ModelField() bits=%d\n",
			m_val.bits());
     */
}

ModelField::~ModelField() {

}

void ModelField::addConstraint(
    IModelConstraint        *c,
    bool                    owned) {
	m_constraints.push_back(IModelConstraintUP(c, owned));
}

void ModelField::addField(
    IModelField             *field,
    bool                    owned) {
	field->setParent(this);
	m_fields.push_back(IModelFieldUP(field, owned));
}

IModelField *ModelField::getField(int32_t idx) {
	if (idx >= 0 && idx < m_fields.size()) {
		return m_fields.at(idx).get();
	} else {
		return 0;
	}
}

void ModelField::setFieldData(IModelFieldData *data) {
	m_data = IModelFieldDataUP(data);
}

IModelFieldData *ModelField::getFieldData() {
	return m_data.get();
}


}
} /* namespace vsc */


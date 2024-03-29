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
 * ModelFieldType.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "ModelFieldType.h"
#include "DataTypeWidthVisitor.h"

namespace vsc {
namespace dm {

ModelFieldType::ModelFieldType(
        ITypeField      *type,
        const ValRef    &val) :
		m_type(type), m_parent(0), m_val(val), m_flags(ModelFieldFlag::NoFlags) {

	if ((type->getAttr() & TypeFieldAttr::Rand) != TypeFieldAttr::NoAttr) {
		m_flags |= ModelFieldFlag::DeclRand;
	}
}

ModelFieldType::~ModelFieldType() {
	// TODO Auto-generated destructor stub
}

void ModelFieldType::addConstraint(
    IModelConstraint        *c,
    bool                    owned) {
	m_constraints.push_back(IModelConstraintUP(c, owned));
}

void ModelFieldType::addField(
    IModelField             *field,
    bool                    owned) {
	field->setParent(this);
	m_fields.push_back(IModelFieldUP(field, owned));
}

IModelField *ModelFieldType::getField(int32_t idx) {
	if (idx >= 0 && idx < m_fields.size()) {
		return m_fields.at(idx).get();
	} else {
		return 0;
	}
}

ValRef ModelFieldType::getImmVal() const {
	return ValRef();
}

ValRef ModelFieldType::getMutVal() const {
	return ValRef();
}

void ModelFieldType::setFieldData(IModelFieldData *data) {
	m_field_data = IModelFieldDataUP(data);
}

IModelFieldData *ModelFieldType::getFieldData() {
	return m_field_data.get();
}

}
} /* namespace vsc */

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

namespace vsc {

ModelField::ModelField() : m_parent(0), m_flags(0) {
	// TODO Auto-generated constructor stub

}

ModelField::ModelField(DataType *type) :
		m_parent(0), m_val(32), m_flags(0) {
	// TODO: obtain actual width
	fprintf(stdout, "ModelField::ModelField() bits=%d\n",
			m_val.bits());
}

ModelField::~ModelField() {
	// TODO Auto-generated destructor stub
}

void ModelField::add_constraint(ModelConstraint *c) {
	m_constraints.push_back(ModelConstraintUP(c));
}

void ModelField::add_field(ModelField *field) {
	field->parent(this);
	m_fields.push_back(ModelFieldUP(field));
}
	void add_constraint(ModelConstraint *c);

} /* namespace vsc */

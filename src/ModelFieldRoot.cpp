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
 * ModelFieldRoot.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "ModelFieldRoot.h"

namespace vsc {

ModelFieldRoot::ModelFieldRoot(
		IDataType			*type,
		const std::string	&name) :
				m_type(type), m_name(name), m_parent(0), m_flags(ModelFieldFlag::NoFlags) {

}

ModelFieldRoot::~ModelFieldRoot() {
	// TODO Auto-generated destructor stub
}

void ModelFieldRoot::addConstraint(IModelConstraint *c) {
	m_constraints.push_back(IModelConstraintUP(c));
}

void ModelFieldRoot::addField(IModelField *field) {
	field->setParent(this);
	m_fields.push_back(IModelFieldUP(field));
}

IModelField *ModelFieldRoot::getField(int32_t idx) {
	if (idx >= 0 && idx < m_fields.size()) {
		return m_fields.at(idx).get();
	} else {
		return 0;
	}
}

} /* namespace vsc */

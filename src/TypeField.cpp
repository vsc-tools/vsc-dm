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
 * TypeField.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#include "TypeField.h"
#include "vsc/dm/IDataTypeStruct.h"

namespace vsc {
namespace dm {

TypeField::TypeField(
		const std::string		&name,
		IDataType				*type,
		bool					own_type,
		TypeFieldAttr			attr) :
				m_parent(0), m_idx(-1), m_name(name), m_type(type), m_attr(attr) {
	if (own_type) {
		m_type_owned = vsc::dm::IDataTypeUP(type);
	}

}

TypeField::~TypeField() {
	// TODO Auto-generated destructor stub
}

ITypeField *TypeField::getField(int32_t idx) const {
	IDataTypeStruct *s = dynamic_cast<IDataTypeStruct *>(getDataType());
	if (s) {
		return s->getField(idx);
	} else {
		return 0;
	}
}

IModelField *TypeField::mkModelField(
		IModelBuildContext 			*ctxt) {
	return getDataType()->mkTypeField(ctxt, this);
}

}
} /* namespace vsc */


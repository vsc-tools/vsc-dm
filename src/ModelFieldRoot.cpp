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
#include "DataTypeWidthVisitor.h"

namespace vsc {
namespace dm {

ModelFieldRoot::ModelFieldRoot(
		IDataType			*type,
		const std::string	&name,
        const ValRef        &val) : m_type(type), m_name(name) {
    m_val = val;

	if (type) {
		std::pair<bool, int32_t> width = DataTypeWidthVisitor().width(type);
		if (width.second > 0) {
//			m_val.setBits(width.second);
		}
	}
}

ModelFieldRoot::~ModelFieldRoot() {
	// TODO Auto-generated destructor stub
}

void ModelFieldRoot::setDataType(IDataType *t) { 
	m_type = t; 
	std::pair<bool, int32_t> width = DataTypeWidthVisitor().width(t);
	if (width.second > 0) {
//		m_val.setBits(width.second);
	}
}

}
} /* namespace vsc */


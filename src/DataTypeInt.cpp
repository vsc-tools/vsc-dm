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
 * DataTypeInt.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#include "vsc/impl/TaskIsTypeFieldRef.h"
#include "DataTypeInt.h"
#include "TypeExprRangelist.h"

namespace vsc {

DataTypeInt::DataTypeInt(
		bool				is_signed,
		int32_t				width) : m_is_signed(is_signed), m_width(width) {
	// TODO Auto-generated constructor stub

}

DataTypeInt::~DataTypeInt() {
	// TODO Auto-generated destructor stub
}

ITypeExprRangelist *DataTypeInt::getDomain() {
	if (!m_domain) {
		m_domain = ITypeExprRangelistUP(new TypeExprRangelist());
		if (m_is_signed) {

		} else {

		}
	}
	return m_domain.get();
}

IModelField *DataTypeInt::mkRootField(
	IModelBuildContext	*ctxt,
	const std::string	&name,
	bool				is_ref) {
	IModelField *ret;
	
	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name);
	}

	return ret;
}

IModelField *DataTypeInt::mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type) {
	IModelField *ret;

	if (TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ITypeFieldPhy *type_p = dynamic_cast<ITypeFieldPhy *>(type);
		ret = ctxt->ctxt()->mkModelFieldType(type);
		if (type_p->getInit()) {
			ret->val()->set(type_p->getInit());
		}
	}

	return ret;
}

} /* namespace vsc */

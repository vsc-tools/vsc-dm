/*
 * DataTypeList.cpp
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "DataTypeList.h"


namespace vsc {
namespace dm {


DataTypeList::DataTypeList(
    IDataType       *elem_t) : m_elem_t(elem_t) {

}

DataTypeList::~DataTypeList() {

}

void DataTypeList::initVal(ValRef &v) {

}

void DataTypeList::finiVal(ValRef &v) {

}

ValRef DataTypeList::copyVal(const ValRef &src) {

}

IModelField *DataTypeList::mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) {
	IModelField *ret;
	
	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt->ctxt()->mkModelFieldRoot(
            this, 
            name,
            ValRef()); // TODO:
//            m_ctxt->mkValRefArr(this));
	}

	return ret;
}

IModelField *DataTypeList::mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) {
	IModelField *ret;

	if (TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ITypeFieldPhy *type_p = dynamic_cast<ITypeFieldPhy *>(type);
        if (type_p) {
    		ret = ctxt->ctxt()->mkModelFieldType(type, val);
		    if (type_p->getInit()) {
            // TODO:
//			ret->val()->set(type_p->getInit());
		    }
        }
	}

	return ret;
}

void DataTypeList::accept(IVisitor *v) {
    v->visitDataTypeList(this);
}

}
}

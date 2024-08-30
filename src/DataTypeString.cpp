/*
 * DataTypeString.cpp
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
#include "DataTypeString.h"
#include "vsc/dm/impl/ValRefStr.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"


namespace vsc {
namespace dm {


DataTypeString::DataTypeString(IContext *ctxt) : DataType(ctxt) {
    // String is represented by a pointer
    m_bytesz = ValRefInt::native_sz();
}

DataTypeString::~DataTypeString() {

}

void DataTypeString::initVal(ValRef &v) {
    ValRefStr vs = m_ctxt->mkValRefStr("");
    v.set(vs);
}

void DataTypeString::finiVal(ValRef &v) {
    Val *val = Val::ValPtr2Val(v.vp());
    m_ctxt->freeVal(val);
}

ValRef DataTypeString::copyVal(const ValRef &src) {
    ValRefStr src_v(src);
    return m_ctxt->mkValRefStr(src_v.val_s());
}

IModelField *DataTypeString::mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) {
	IModelField *ret;
	
	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
//        ValRefStr val(vsc::dm::ValRef());
        ValRef val;
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name, val);
	}

	return ret;
}

IModelField *DataTypeString::mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) {
	IModelField *ret;

	if (TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ITypeFieldPhy *type_p = dynamic_cast<ITypeFieldPhy *>(type);
		ret = ctxt->ctxt()->mkModelFieldType(type, val);
		if (type_p->getInit()) {
            // TODO:
//			ret->val()->set(type_p->getInit());
		}
	}

	return ret;
}

void DataTypeString::accept(IVisitor *v) {
    v->visitDataTypeString(this);
}

}
}

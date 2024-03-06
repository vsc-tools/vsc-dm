/*
 * DataTypePtr.cpp
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
#include "vsc/dm/impl/ValRefInt.h"
#include "vsc/dm/impl/ValRefPtr.h"
#include "DataTypePtr.h"


namespace vsc {
namespace dm {


DataTypePtr::DataTypePtr(IContext *ctxt) : DataType(ctxt) {
    m_bytesz = sizeof(void *);
}

DataTypePtr::~DataTypePtr() {

}

void DataTypePtr::initVal(ValRef &v) {
    ValRefPtr val_p(v);
    val_p.set_val(0);
}

void DataTypePtr::finiVal(ValRef &v) {

}

ValRef DataTypePtr::copyVal(const ValRef &src) {
	return ValRef();
}

void DataTypePtr::accept(IVisitor *v) {
    v->visitDataTypePtr(this);
}

IModelField *DataTypePtr::mkRootField(
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
            m_ctxt->mkValRefRawPtr(0));
	}

	return ret;
}

IModelField *DataTypePtr::mkTypeField(
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
		    if (type_p->getInit().isVoid()) {
            // TODO:
//			ret->val()->set(type_p->getInit());
		    }
        }
	}

	return ret;
}

}
}

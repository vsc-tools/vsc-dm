/*
 * DataTypeBool.cpp
 *
 * Copyright 2022 Matthew Ballance and Contributors
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
#include "DataTypeBool.h"
#include "ModelVal.h"


namespace vsc {
namespace dm {


DataTypeBool::DataTypeBool(IContext *ctxt) {
    m_domain = ITypeExprRangelistUP(ctxt->mkTypeExprRangelist());
    ModelVal v0, v1;
    v0.set_val_u(0, 1);
    v1.set_val_u(1, 1);

    m_domain->addRange(ctxt->mkTypeExprRange(
        false,
        ctxt->mkTypeExprVal(&v0),
        ctxt->mkTypeExprVal(&v1)
    ));
}

DataTypeBool::~DataTypeBool() {

}

IModelField *DataTypeBool::mkRootField(
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

IModelField *DataTypeBool::mkTypeField(
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

}
}

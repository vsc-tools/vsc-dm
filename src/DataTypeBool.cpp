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
#include "vsc/dm/impl/ValRefBool.h"
#include "DataTypeBool.h"
#include "ModelVal.h"


namespace vsc {
namespace dm {


DataTypeBool::DataTypeBool(IContext *ctxt) {
    m_domain = ITypeExprRangelistUP(ctxt->mkTypeExprRangelist());
    ValData v0, v1;

    v0 = 0;
    v1 = 1;

    m_domain->addRange(ctxt->mkTypeExprRange(
        false,
        ctxt->mkTypeExprVal(this, v0),
        ctxt->mkTypeExprVal(this, v1)
    ));

    m_bytesz = sizeof(bool);
}

DataTypeBool::~DataTypeBool() {

}

void DataTypeBool::initVal(ValRef &v) {
    ValRefBool vr(v);
    vr.set_val(false);
}

ValRef &&DataTypeBool::copyVal(const ValRef &src) {
    ValRefBool src_b(src);
    ValRefBool cpy;
    cpy.set_val(src_b.get_val());
    return std::move(cpy);
}

IModelField *DataTypeBool::mkRootField(
	IModelBuildContext	*ctxt,
	const std::string	&name,
	bool				is_ref) {
	IModelField *ret;
	
	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
        ValRefBool val;
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name, val);
	}

	return ret;
}

IModelField *DataTypeBool::mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) {
	IModelField *ret;

	if (TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ITypeFieldPhy *type_p = dynamic_cast<ITypeFieldPhy *>(type);
		ret = ctxt->ctxt()->mkModelFieldType(type, val);
		if (type_p->getInit().isVoid()) {
            // TODO:
//			ret->val()->set(type_p->getInit());
		}
	}

	return ret;
}

}
}

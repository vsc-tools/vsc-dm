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

#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "vsc/dm/impl/ValRefInt.h"
#include "DataTypeInt.h"
#include "TypeExprRangelist.h"

namespace vsc {
namespace dm {

DataTypeInt::DataTypeInt(
		bool				is_signed,
		int32_t				width) : m_is_signed(is_signed), m_width(width) {
    if (width <= ValRefInt::native_sz()) {
        m_bytesz = ((width-1)/8)+1;
    } else {
        m_bytesz = ((width-1)/ValRefInt::native_sz())*(ValRefInt::native_sz()/8);
    }
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

void DataTypeInt::initVal(ValRef &v) {
    ValRefInt vi(v);
    vi.clear();
}

void DataTypeInt::finiVal(ValRef &v) {
    if ((v.flags() & ValRef::Flags::Owned) != ValRef::Flags::None) {
        // Return the storage
        Val *val = Val::ValPtr2Val(v.vp());
        val->p.ap->freeVal(val);
    }
}

ValRef DataTypeInt::copyVal(const ValRef &src) {
    ValRefInt src_i(src);
    if (src_i.bits() <= ValRefInt::native_sz()) {
        // Can just copy over
        ValRefInt cpy();
    } else {
        // Need to alloc new storage

    }
}

IModelField *DataTypeInt::mkRootField(
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
            m_ctxt->mkValRefInt(0, isSigned(), getWidth()));
	}

	return ret;
}

IModelField *DataTypeInt::mkTypeField(
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
} /* namespace vsc */

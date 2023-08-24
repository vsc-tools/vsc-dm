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
 * DataTypeStruct.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "vsc/dm/impl/TaskBuildModelConstraint.h"
#include "vsc/dm/impl/ValRefInt.h"
#include "DataTypeStruct.h"
#include "TypeField.h"
#include "TypeConstraint.h"

namespace vsc {
namespace dm {

DataTypeStruct::DataTypeStruct(const std::string &name) : m_name(name) {
    m_bytesz = 0;
}

DataTypeStruct::~DataTypeStruct() {
	// TODO Auto-generated destructor stub
}

void DataTypeStruct::addField(
    ITypeField      *f,
    bool            owned) {
	f->setIndex(m_fields.size());
    int32_t offset = m_bytesz;
    if (m_fields.size()) {
        int32_t new_sz = f->getDataType()->getByteSize();
        int32_t align = 1;
        if (new_sz <= ValRefInt::native_sz()) {
            align = new_sz;
        } else {
            // The new field is larger. Think we might have to inspect...
        }

        // Required
        int32_t pad = (m_bytesz%align)?(align - (m_bytesz % align)):0;
        offset += pad;
        m_bytesz += pad;
    }

    m_bytesz += f->getDataType()->getByteSize();
    fprintf(stdout, "offset: %d\n", offset);
    f->setOffset(offset);
	m_fields.push_back(ITypeFieldUP(f, owned));
}

const std::vector<ITypeFieldUP> &DataTypeStruct::getFields() const {
	return m_fields;
}

ITypeField *DataTypeStruct::getField(int32_t idx) {
	if (idx < 0 || idx >= m_fields.size()) {
		return 0;
	} else {
		return m_fields.at(idx).get();
	}
}

void DataTypeStruct::initVal(ValRef &v) {
    ValRefStruct vs(v);

    for (uint32_t i=0; i<vs.getNumFields(); i++) {
        ValRef vs_f(vs.getField(i));
        vs_f.type()->initVal(vs_f);
    }
}

void DataTypeStruct::finiVal(ValRef &v) {
    ValRefStruct vs(v);

    for (uint32_t i=0; i<vs.getNumFields(); i++) {
        ValRef vs_f(vs.getField(i));
        vs_f.type()->finiVal(vs_f);
    }

    if ((v.flags() & ValRef::Flags::Owned) != ValRef::Flags::None) {
        Val *val = Val::ValPtr2Val(v.vp());
        val->p.ap->freeVal(val);
    }
}

ValRef &&DataTypeStruct::copyVal(const ValRef &src) {
    ValRefStruct src_s(src);
    Val *cpy_v = m_ctxt->mkVal(src_s.type()->getByteSize());
    ValRefStruct cpy(
        Val::Val2ValPtr(cpy_v),
        dynamic_cast<IDataTypeStruct *>(src.type()),
        ValRef::Flags::Owned);

}

void DataTypeStruct::addConstraint(
    ITypeConstraint     *c,
    bool                owned) {
	m_constraints.push_back(ITypeConstraintUP(c, owned));
}

const std::vector<ITypeConstraintUP> &DataTypeStruct::getConstraints() const {
	return m_constraints;
}

IModelField *DataTypeStruct::mkRootField(
	IModelBuildContext	*ctxt,
	const std::string	&name,
	bool				is_ref) {
    ValRefStruct val(ctxt->ctxt()->mkValRefStruct(this));
	IModelField *ret;

	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name);

        ctxt->pushTopDownScope(ret);

		// Need to build sub-fields and constraints

		for (uint32_t i=0; i<getFields().size(); i++) {
			ret->addField(
                getFields().at(i)->mkModelField(
                    ctxt,
                    val.getField(i)), true);
		}
	
		for (std::vector<ITypeConstraintUP>::const_iterator
			it=getConstraints().begin();
			it!=getConstraints().end(); it++) {
			// TODO:
			ret->addConstraint(TaskBuildModelConstraint<>(ctxt).build(it->get()), true);
		}

        ctxt->popTopDownScope();
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

IModelField *DataTypeStruct::mkTypeField(
	IModelBuildContext	*ctxt,
	ITypeField			*type,
    const ValRef        &val) {
	IModelField *ret;

	if (TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
        ValRefStruct val_s(val);
		ret = ctxt->ctxt()->mkModelFieldType(type, val);

        ctxt->pushTopDownScope(ret);

		for (uint32_t i=0; i<getFields().size(); i++) {
			ret->addField(
                getFields().at(i)->mkModelField(
                    ctxt,
                    val_s.getField(i)), true);
		}
	
		for (std::vector<ITypeConstraintUP>::const_iterator
			it=getConstraints().begin();
			it!=getConstraints().end(); it++) {
			// TODO:
			ret->addConstraint(TaskBuildModelConstraint<>(ctxt).build(it->get()), true);
		}

        ctxt->popTopDownScope();
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

}
} /* namespace vsc */

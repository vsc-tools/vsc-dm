/*
 * ModelFieldVec.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 * 
 * Copyright 2019-2023 Matthew Ballance and contributors
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
 */

#include "ModelFieldVec.h"

namespace vsc {
namespace dm {

ModelFieldVec::ModelFieldVec(IContext *ctxt) {
	IDataTypeInt *ui32_t = ctxt->findDataTypeInt(false, 32);
	if (!ui32_t) {
		ui32_t = ctxt->mkDataTypeInt(false, 32);
		ctxt->addDataTypeInt(ui32_t);
	}
	m_size = IModelFieldUP(ctxt->mkModelFieldRoot(ui32_t, "size"));
	m_size->setParent(this);
	m_size->val()->setBits(32);
	m_size->setFlag(ModelFieldFlag::VecSize);
}

ModelFieldVec::~ModelFieldVec() {
	// TODO Auto-generated destructor stub
}

void ModelFieldVec::push_back(IModelField *f) {
	m_fields.push_back(IModelFieldUP(f));
}

IModelField *ModelFieldVec::at(uint32_t idx) {
	if (idx < m_fields.size()) {
		return m_fields.at(idx).get();
	} else {
		return 0;
	}
}

void ModelFieldVec::pop_back() {
	m_fields.pop_back();
}

}
} /* namespace vsc */


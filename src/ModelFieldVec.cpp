/*
 * ModelFieldVec.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#include "ModelFieldVec.h"

namespace vsc {

ModelFieldVec::ModelFieldVec(IContext *ctxt) {
	IDataTypeInt *ui32_t = ctxt->findDataTypeInt(false, 32);
	if (!ui32_t) {
		ui32_t = ctxt->mkDataTypeInt(false, 32);
		ctxt->addDataTypeInt(ui32_t);
	}
	m_size = IModelFieldUP(ctxt->mkModelFieldRoot(ui32_t, "size"));
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

} /* namespace vsc */

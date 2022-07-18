/*
 * TypeFieldVec.cpp
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#include "TypeFieldVec.h"

namespace vsc {

TypeFieldVec::TypeFieldVec(
		IContext			*ctxt,
		const std::string	&name,
		IDataType			*type,
		bool				own_type,
		TypeFieldAttr		attr,
		IModelVal			*init_sz) : TypeField(
				name, type, own_type, attr), m_init_sz(init_sz) {
	IDataTypeInt *ui32_t = ctxt->findDataTypeInt(false, 32);
	if (!ui32_t) {
		ui32_t = ctxt->mkDataTypeInt(false, 32);
		ctxt->addDataTypeInt(ui32_t);
	}
	m_size = ITypeFieldUP(ctxt->mkTypeFieldPhy(
			"size",
			ui32_t,
			false,
			TypeFieldAttr::VecSize, 0));
}

TypeFieldVec::~TypeFieldVec() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

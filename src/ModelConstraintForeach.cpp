/*
 * ModelConstraintForeach.cpp
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#include "ModelConstraintForeach.h"

namespace vsc {

ModelConstraintForeach::ModelConstraintForeach(
	IContext 			*ctxt,
	IModelExpr			*target,
	const std::string	&index_it_name) : m_target(target) {

	IDataTypeInt *vsc_uint32_t = ctxt->findDataTypeInt(false, 32);
	if (!vsc_uint32_t) {
		vsc_uint32_t = ctxt->mkDataTypeInt(false, 32);
		ctxt->addDataTypeInt(vsc_uint32_t);
	}

	m_index_it = IModelFieldUP(ctxt->mkModelFieldRoot(vsc_uint32_t, index_it_name));
}

ModelConstraintForeach::~ModelConstraintForeach() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

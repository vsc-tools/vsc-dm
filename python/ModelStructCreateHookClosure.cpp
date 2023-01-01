/*
 * ModelStructCreateHookClosure.cpp
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#include "ModelStructCreateHookClosure.h"
#include "vsc/dm/IModelExprBin.h"
#include "core.h"

namespace vsc {
namespace dm {

ModelStructCreateHookClosure::ModelStructCreateHookClosure(PyObject *obj) {
	m_obj = obj;
	Py_INCREF(m_obj);
}

ModelStructCreateHookClosure::~ModelStructCreateHookClosure() {
	Py_DECREF(m_obj);
}

void ModelStructCreateHookClosure::create(IModelField *field) {
	model_struct_create_hook_closure_invoke(m_obj, field);
}

}
} /* namespace vsc */

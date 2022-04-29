/*
 * ModelFieldDataClosure.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include "ModelFieldDataClosure.h"

namespace vsc {

ModelFieldDataClosure::ModelFieldDataClosure(PyObject *data) : m_data(data) {
	Py_INCREF(m_data);
}

ModelFieldDataClosure::~ModelFieldDataClosure() {
	Py_DECREF(m_data);
}

} /* namespace vsc */

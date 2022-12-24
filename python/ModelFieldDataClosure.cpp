/*
 * ModelFieldDataClosure.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include <stdio.h>
#include "ModelFieldDataClosure.h"

namespace vsc {
namespace dm {

ModelFieldDataClosure::ModelFieldDataClosure(PyObject *data) : m_data(data) {
	Py_INCREF(m_data);
}

ModelFieldDataClosure::~ModelFieldDataClosure() {
	// Decrementing the reference can cause a crash on exit
	if (m_data) {
		Py_DECREF(m_data);
		m_data = 0;
	}
}

PyObject *ModelFieldDataClosure::getData() {
	// Assume the caller will dec ref
	Py_INCREF(m_data);
	return m_data;
}

}
} /* namespace vsc */

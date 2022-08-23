/*
 * ModelFieldDataClosure.h
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#pragma once
#include <Python.h>
#include "vsc/IModelFieldData.h"

namespace vsc {

class ModelFieldDataClosure : public IModelFieldData {
public:
	ModelFieldDataClosure(PyObject *data);

	virtual ~ModelFieldDataClosure();

	PyObject *getData();

private:
	PyObject				*m_data;

};

} /* namespace vsc */


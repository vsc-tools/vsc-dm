/*
 * ModelField.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#include "ModelField.h"

namespace vsc {

ModelField::ModelField() : m_parent(0) {
	// TODO Auto-generated constructor stub

}

ModelField::ModelField(DataType *type) : m_parent(0), m_val(type) {

}

ModelField::~ModelField() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

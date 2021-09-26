/*
 * TypeField.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#include "TypeField.h"

namespace vsc {

TypeField::TypeField(
		DataTypeStruct			*parent,
		const std::string		&name,
		DataType				*type,
		TypeFieldAttr			attr,
		ModelVal				*init) :
				m_parent(parent), m_name(name), m_type(type), m_attr(attr),
				m_init(init) {
	// TODO Auto-generated constructor stub

}

TypeField::~TypeField() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

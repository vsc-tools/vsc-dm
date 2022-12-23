/*
 * ModelFieldRefRoot.cpp
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */
#include "DataTypeWidthVisitor.h"
#include "ModelFieldRefRoot.h"

namespace vsc {
namespace dm {

ModelFieldRefRoot::ModelFieldRefRoot(
		IDataType			*type,
		const std::string	&name) : m_type(type), m_name(name) {
	// TODO Auto-generated constructor stub

}

ModelFieldRefRoot::~ModelFieldRefRoot() {
	// TODO Auto-generated destructor stub
}

void ModelFieldRefRoot::setDataType(IDataType *t) {
	m_type = t;
	val()->setBits(DataTypeWidthVisitor().width(t).second);
}

}
} /* namespace vsc */


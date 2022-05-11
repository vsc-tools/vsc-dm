/*
 * TypeFieldPhy.cpp
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#include "TypeFieldPhy.h"

namespace vsc {

TypeFieldPhy::TypeFieldPhy(
		const std::string	&name,
		IDataType			*type,
		TypeFieldAttr		attr,
		IModelVal			*init) : TypeField(name, type, attr), m_init(init) {

}

TypeFieldPhy::~TypeFieldPhy() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
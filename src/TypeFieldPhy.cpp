/*
 * TypeFieldPhy.cpp
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#include "TypeFieldPhy.h"

namespace vsc {
namespace dm {

TypeFieldPhy::TypeFieldPhy(
		const std::string	&name,
		IDataType			*type,
		bool				own_type,
		TypeFieldAttr		attr,
        const ValRef        &init) :
		    TypeField(name, type, own_type, attr), m_init(init) {

}

TypeFieldPhy::~TypeFieldPhy() {
	// TODO Auto-generated destructor stub
}	

}
} /* namespace vsc */


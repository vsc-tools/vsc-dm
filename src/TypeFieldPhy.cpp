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
        ValData             init,
        bool                have_init) :
		    TypeField(name, type, own_type, attr), 
            m_init(init), m_haveInit(have_init) {

}

TypeFieldPhy::~TypeFieldPhy() {
	// TODO Auto-generated destructor stub
}	

}
} /* namespace vsc */


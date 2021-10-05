/*
 * ctor_ctxt.cpp
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#include "ctor_ctxt.h"

namespace vsc {
namespace facade {

ctor_ctxt::ctor_ctxt(
		const std::string		&name,
		rand_obj				*scope,
		const std::type_info	*ti) :
				m_name(name), m_scope(scope), m_ti(ti) {

}

ctor_ctxt::~ctor_ctxt() {
	// TODO Auto-generated destructor stub
}

} /* namespace facade */
} /* namespace vsc */

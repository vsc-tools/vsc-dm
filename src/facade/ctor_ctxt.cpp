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
		rand_obj				*scope):
				m_name(name), m_scope(scope),
				m_is_scope(false) {

}

ctor_ctxt::~ctor_ctxt() {
	// TODO Auto-generated destructor stub
}

const std::type_info *ctor_ctxt::ti() const {
	return (m_ti_s.size())?m_ti_s.back():0;
}

void ctor_ctxt::push_ti(const std::type_info *t) {
	m_ti_s.push_back(t);
}

void ctor_ctxt::pop_ti() {
	m_ti_s.pop_back();
}

} /* namespace facade */
} /* namespace vsc */

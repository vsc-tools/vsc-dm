/*
 * scope_base.cpp
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */
#include <stdio.h>
#include "ctor.h"
#include "scope_base.h"

namespace vsc {
namespace facade {

scope_base::scope_base(const std::string &name) :
	m_name(name), m_scope(0), m_ti(0) {
	ctor::inst()->scope_ctor(name, 0, 0);
}

scope_base::scope_base(
		rand_obj				*s,
		const std::type_info	&ti) :
			m_scope(s), m_ti(&ti) {
	ctor::inst()->scope_ctor("", s, &ti);
}

scope_base::scope_base(
		rand_obj				*s,
		const std::type_info	&ti,
		const std::string		&name) :
			m_name(name), m_scope(s), m_ti(&ti) {
	ctor::inst()->scope_ctor(name, s, &ti);
}

scope_base::~scope_base() {
	ctor::inst()->scope_dtor(m_name, m_scope, m_ti);
}

} /* namespace facade */
} /* namespace vsc */

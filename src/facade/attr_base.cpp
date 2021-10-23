/*
 * attr_base.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "attr_base.h"
#include "ctor.h"
#include "rand_obj.h"

namespace vsc {
namespace facade {

attr_base::attr_base() : m_field(0), m_idx(-1) {
	m_name = ctor::inst()->scope_name();
	m_parent = ctor::inst()->scope(this);

	if (!m_parent) {

	}

	fprintf(stdout, "attr_base: %s %p\n", m_name.c_str(), m_parent);
}

attr_base::~attr_base() {
	// TODO Auto-generated destructor stub
}

std::string attr_base::fullname() const {
	std::string ret = m_name;

	attr_base *p = m_parent;
	while (p) {
		ret.insert(0, ".");
		ret.insert(0, p->m_name);
		p = p->m_parent;
	}

	return ret;
}

void attr_base::build_constraints() {

}

} /* namespace facade */
} /* namespace vsc */

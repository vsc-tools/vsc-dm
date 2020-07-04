/*
 * Field.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "Field.h"

namespace vsc {

Field::Field(const std::string &name, bool is_rand) :
		m_name(name), m_parent(0), m_idx(-1),
		m_decl_rand(is_rand), m_used_rand(false) {
	// TODO Auto-generated constructor stub

}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

std::string Field::fullname() const {
	std::string ret = m_name;

	Field *p = m_parent;
	while (p) {
		ret.insert(0, "::");
		ret.insert(0, p->name());
		p = p->parent();
	}

	return ret;
}

void Field::set_used_rand(bool used_rand, int32_t level) {
	m_used_rand = (used_rand && (m_decl_rand || level == 0));
}

} /* namespace vsc */

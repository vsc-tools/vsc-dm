/*
 * FieldComposite.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "FieldComposite.h"

namespace vsc {

FieldComposite::FieldComposite(const std::string &name, bool is_rand) :
	Field(name, is_rand) {
	// TODO Auto-generated constructor stub

}

FieldComposite::~FieldComposite() {
	// TODO Auto-generated destructor stub
}

void FieldComposite::set_used_rand(bool used_rand, int32_t level) {
	Field::set_used_rand(used_rand, level);
	for (std::vector<FieldSP>::const_iterator it=m_children.begin();
			it!=m_children.end(); it++) {
		(*it)->set_used_rand(used_rand, level+1);
	}
}

} /* namespace vsc */

/*
 * rand_obj.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "rand_obj.h"

namespace vsc {
namespace facade {

rand_obj::rand_obj(const scope &s) {
	m_field = new ModelFieldRoot(0, m_name);


	if (m_parent) {
		// Model belongs to the parent scope
		fprintf(stdout, "[%s] parent=%p field=%p\n",
				parent()->fullname().c_str(), parent(), parent()->field());
		parent()->field()->add_field(m_field);
	} else {
		// We own the field since there is no parent scope
		m_field_u = ModelFieldRootUP(m_field);
	}
}

rand_obj::~rand_obj() {
	// TODO Auto-generated destructor stub
}

bool rand_obj::randomize() {
	return false;
}

bool rand_obj::randomize_with(
		const std::function<void()> &body) {

	return false;
}

} /* namespace facade */
} /* namespace vsc */

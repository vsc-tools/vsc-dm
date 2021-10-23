/*
 * constraint.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "constraint.h"
#include "rand_obj.h"
#include "ctor.h"

namespace vsc {
namespace facade {

constraint::constraint(
		const std::function<void ()>	&body) : m_body(body) {
	rand_obj *scope = ctor::inst()->scope();
	scope->add_constraint(this);
}

constraint::constraint(
		const std::string				&name,
		const std::function<void ()>	&body) :
				m_name(name), m_body(body) {
	rand_obj *scope = ctor::inst()->scope();
	scope->add_constraint(this);
}

constraint::~constraint() {
	// TODO Auto-generated destructor stub
}

} /* namespace facade */
} /* namespace vsc */

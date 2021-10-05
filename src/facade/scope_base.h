/*
 * scope_base.h
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include <typeinfo>

namespace vsc {
namespace facade {

class rand_obj;

class scope_base {
public:
	scope_base(const std::string &name);

	scope_base(
			rand_obj				*s,
			const std::type_info 	&ti);

	scope_base(
			rand_obj				*s,
			const std::type_info 	&ti,
			const std::string		&name);

	virtual ~scope_base();

	const std::string &name() const { return m_name; }


private:
	std::string						m_name;
	rand_obj						*m_scope;
	const std::type_info			*m_ti;

};

} /* namespace facade */
} /* namespace vsc */


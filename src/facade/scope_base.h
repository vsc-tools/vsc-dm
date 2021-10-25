/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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


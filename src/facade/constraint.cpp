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
	fprintf(stdout, "--> constraint\n");
	fflush(stdout);
	rand_obj *scope = ctor::inst()->scope();
	scope->add_constraint(this);
	fprintf(stdout, "<-- constraint\n");
	fflush(stdout);
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

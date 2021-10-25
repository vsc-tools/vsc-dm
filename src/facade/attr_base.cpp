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
 * attr_base.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "Debug.h"
#include "attr_base.h"
#include "ctor.h"
#include "rand_obj.h"

#undef EN_DEBUG_ATTR_BASE

#ifdef EN_DEBUG_ATTR_BASE
DEBUG_SCOPE(attr_base)
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(attr_base, fmt, ##_VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(attr_base, fmt, ##_VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(attr_base, fmt, ##_VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {
namespace facade {

attr_base::attr_base() : m_field(0), m_idx(-1) {
	DEBUG_ENTER("attr_base")
	m_name = ctor::inst()->scope_name();
	m_parent = ctor::inst()->scope(this);

	if (!m_parent) {

	}

	DEBUG("%s %p", m_name.c_str(), m_parent);

	DEBUG_LEAVE("attr_base")
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

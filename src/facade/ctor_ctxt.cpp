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
 * ctor_ctxt.cpp
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#include "ctor_ctxt.h"

namespace vsc {
namespace facade {

ctor_ctxt::ctor_ctxt(
		const std::string		&name,
		obj						*scope):
				m_name(name), m_scope(scope),
				m_is_scope(false) {

}

ctor_ctxt::~ctor_ctxt() {
	// TODO Auto-generated destructor stub
}

const std::type_info *ctor_ctxt::ti() const {
	return (m_ti_s.size())?m_ti_s.back():0;
}

void ctor_ctxt::push_ti(const std::type_info *t) {
	m_ti_s.push_back(t);
}

void ctor_ctxt::pop_ti() {
	m_ti_s.pop_back();
}

} /* namespace facade */
} /* namespace vsc */

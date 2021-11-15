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
 * ctor_ctxt.h
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include <vector>

namespace vsc {
namespace facade {

class obj;

class ctor_ctxt;
using ctor_ctxt_up = std::unique_ptr<ctor_ctxt>;
class ctor_ctxt {
public:
	ctor_ctxt(
			const std::string		&name,
			obj						*scope);

	virtual ~ctor_ctxt();

	const std::string &name() const { return m_name; }

	void name(const std::string &n) { m_name = n; }

	obj *scope() const { return m_scope; }

	void scope(obj *s) { m_scope = s; }

	bool is_scope() const { return m_is_scope; }

	void is_scope(bool s) { m_is_scope = s; }

	const std::type_info *ti() const;

	void push_ti(const std::type_info *t);

	void pop_ti();

private:
	std::string								m_name;
	bool									m_is_scope;
	obj										*m_scope;
	std::vector<const std::type_info *>		m_ti_s;

};

} /* namespace facade */
} /* namespace vsc */


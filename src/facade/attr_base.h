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
 * attr_base.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "ModelFieldRoot.h"

namespace vsc {
namespace facade {

class attr_base {
	friend class rand_obj;
public:
	attr_base();

	virtual ~attr_base();

	const std::string &name() const { return m_name; }

	void name(const std::string &n) { m_name = n; }

	std::string fullname() const;

	int32_t idx() const { return m_idx; }

	void idx(int32_t i) { m_idx = i; }

	attr_base *parent() const { return m_parent; }

	void parent(attr_base *p) { m_parent = p; }

	ModelField *field() const { return m_field; }

protected:

	virtual void build_constraints();


protected:
	std::string					m_name;
	int32_t						m_idx;
	attr_base					*m_parent;

	ModelFieldRoot				*m_field;
	ModelFieldRootUP			m_field_u;

};

} /* namespace facade */
} /* namespace vsc */


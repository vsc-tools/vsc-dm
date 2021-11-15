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
#include "obj.h"
#include "ModelFieldRoot.h"

namespace vsc {
namespace facade {

class obj_scope;
class attr_base : public obj {
	friend class rand_obj;
	template <class ...T> friend class with_sample;
public:
	attr_base();

	virtual ~attr_base();

	int32_t idx() const { return m_idx; }

	void idx(int32_t i) { m_idx = i; }

	ModelField *field() const { return m_field; }

	ModelField *release() { return m_field_u.release(); }

protected:

	virtual void build();

	virtual void build_constraints();


protected:
	int32_t						m_idx;

	ModelField					*m_field;
	ModelFieldUP				m_field_u;

};

} /* namespace facade */
} /* namespace vsc */


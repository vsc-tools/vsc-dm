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
 * SolveSet.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */

#include "SolveSet.h"

namespace vsc {

SolveSet::SolveSet() {
	// TODO Auto-generated constructor stub

}

SolveSet::~SolveSet() {
	// TODO Auto-generated destructor stub
}

void SolveSet::add_field(ModelField *f) {
	if (m_field_s.find(f) == m_field_s.end()) {
		m_all_fields.push_back(f);
		if (f->is_flag_set(ModelFieldFlag_UsedRand)) {
			m_rand_fields.push_back(f);
		}
		m_field_s.insert(f);
	}
}

void SolveSet::add_constraint(ModelConstraint *c) {
	if (m_constraint_s.find(c) == m_constraint_s.end()) {
		m_constraints.push_back(c);
		m_constraint_s.insert(c);
	}
}

void SolveSet::add_soft_constraint(ModelConstraintSoft *c) {
	if (m_soft_constraint_s.find(c) == m_soft_constraint_s.end()) {
		m_soft_constraints.push_back(c);
		m_soft_constraint_s.insert(c);
	}
}

} /* namespace vsc */

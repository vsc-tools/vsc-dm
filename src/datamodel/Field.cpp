
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Field.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "Field.h"

namespace vsc {

Field::Field(const std::string &name, bool is_rand) :
		m_name(name), m_parent(0), m_idx(-1),
		m_decl_rand(is_rand), m_used_rand(false) {
	// TODO Auto-generated constructor stub

}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

std::string Field::fullname() const {
	std::string ret = m_name;

	Field *p = m_parent;
	while (p) {
		ret.insert(0, "::");
		ret.insert(0, p->name());
		p = p->parent();
	}

	return ret;
}

void Field::set_used_rand(bool used_rand, int32_t level) {
	m_used_rand = (used_rand && (m_decl_rand || level == 0));
}

} /* namespace vsc */


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
 * FieldComposite.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "FieldComposite.h"

namespace vsc {

FieldComposite::FieldComposite(const std::string &name, bool is_rand) :
	Field(name, is_rand) {
	// TODO Auto-generated constructor stub

}

FieldComposite::~FieldComposite() {
	// TODO Auto-generated destructor stub
}

void FieldComposite::set_used_rand(bool used_rand, int32_t level) {
	Field::set_used_rand(used_rand, level);
	for (std::vector<FieldSP>::const_iterator it=m_children.begin();
			it!=m_children.end(); it++) {
		(*it)->set_used_rand(used_rand, level+1);
	}
}

} /* namespace vsc */

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
 * RandFieldCollector.cpp
 *
 *  Created on: Jul 10, 2020
 *      Author: ballance
 */

#include "sav/RandFieldCollector.h"

namespace vsc {

RandFieldCollector::RandFieldCollector() : m_rand_fields(0) {
	// TODO Auto-generated constructor stub

}

RandFieldCollector::~RandFieldCollector() {
	// TODO Auto-generated destructor stub
}

void RandFieldCollector::collect(
		const std::vector<FieldSP>		&fields,
		std::vector<FieldScalar *>		&rand_fields) {
	m_rand_fields = &rand_fields;
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}
}

void RandFieldCollector::visitFieldScalar(FieldScalar *f) {
	m_rand_fields->push_back(f);
}

} /* namespace vsc */

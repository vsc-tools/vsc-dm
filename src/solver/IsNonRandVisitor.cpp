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
 * IsNonRandVisitor.cpp
 *
 *  Created on: Jul 9, 2020
 *      Author: ballance
 */

#include "IsNonRandVisitor.h"

namespace vsc {

IsNonRandVisitor::IsNonRandVisitor() : m_is_nonrand(true) {
	// TODO Auto-generated constructor stub

}

IsNonRandVisitor::~IsNonRandVisitor() {
	// TODO Auto-generated destructor stub
}

bool IsNonRandVisitor::is_nonrand(const ExprSP &expr) {
	m_is_nonrand = true;
	expr->accept(this);

	return m_is_nonrand;
}

void IsNonRandVisitor::visitExprFieldRef(ExprFieldRef *e) {
	if (e->field()->used_rand()) {
		// Definitely references a random field
		m_is_nonrand = false;
	}
}

} /* namespace vsc */

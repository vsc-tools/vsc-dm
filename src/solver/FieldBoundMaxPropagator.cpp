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
 * FieldBoundMaxPropagator.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#include "FieldBoundMaxPropagator.h"

#include "../expr/ExprNumericEvaluator.h"

namespace vsc {

FieldBoundMaxPropagator::FieldBoundMaxPropagator(
		FieldBoundInfo 		*info,
		ExprSP				max_e) : FieldBoundPropagator(info), m_max_e(max_e) {

}

FieldBoundMaxPropagator::~FieldBoundMaxPropagator() {
	// TODO Auto-generated destructor stub
}

void FieldBoundMaxPropagator::propagate() {
	ExprNumericEvaluator eval;
	ExprValNumericSP max_v = eval.eval_num(m_max_e.get());


	domain_t &domain = m_info->domain();
	int32_t i=domain.size()-1;

	// Find the first interval where the minimum is less than the max value
	while (i>0) {
		if (domain.at(i).first->le(max_v.get())) {
			break;
		} else {
			i--;
		}
	}

	bool do_propagate = false;

	if (domain.at(i).second->gt(max_v.get())) {
		domain.at(i).second = max_v;
		do_propagate = true;
	}

	if (i < domain.size()-1) {
		// Trim off range elements, since these are greater
		// than the new max
		do_propagate = true;
		domain.resize(i+1);
	}

	if (do_propagate) {
		m_info->propagate();
	}
}

} /* namespace vsc */

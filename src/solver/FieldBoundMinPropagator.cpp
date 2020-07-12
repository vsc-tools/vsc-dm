
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
 * FieldBoundMinPropagator.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#include "solver/FieldBoundMinPropagator.h"

#include "expr/ExprNumericEvaluator.h"
#include "solver/FieldBoundInfo.h"

namespace vsc {

FieldBoundMinPropagator::FieldBoundMinPropagator(
		FieldBoundInfo		*info,
		ExprSP				min_e) : FieldBoundPropagator(info), m_min_e(min_e) {
	// TODO Auto-generated constructor stub

}

FieldBoundMinPropagator::~FieldBoundMinPropagator() {
	// TODO Auto-generated destructor stub
}

void FieldBoundMinPropagator::propagate() {
	ExprNumericEvaluator eval;
	ExprValNumericSP min_v = eval.eval_num(m_min_e.get());

	domain_t &domain = m_info->domain();
	// TODO: should be 0?
	int32_t i = domain.size()-1;

	while (i < domain.size()-1 && domain.at(i).first->lt(min_v.get())) {
		i++;
	}

	bool do_propagate = false;

	if (i < domain.size()) {
		if (i > 0) {
			// Must trim off full elements
			do_propagate = true;
			domain = domain_t(domain.begin()+i, domain.end());
		}

		if (min_v->gt(domain.at(0).first.get())) {
			// Adjust minimum value
			domain.at(0).first = min_v;
			do_propagate = true;
		}
	}

	if (do_propagate) {
		m_info->propagate();
	}
}

} /* namespace vsc */

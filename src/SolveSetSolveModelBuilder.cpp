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
 * SolveSetSolveModelBuilder.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#include "SolveSetSolveModelBuilder.h"

namespace vsc {

SolveSetSolveModelBuilder::SolveSetSolveModelBuilder(ISolver *solver) :
		m_solver(solver) {
	// TODO Auto-generated constructor stub

}

SolveSetSolveModelBuilder::~SolveSetSolveModelBuilder() {
	// TODO Auto-generated destructor stub
}

void SolveSetSolveModelBuilder::build(SolveSet *sset) {
	for (auto f_it=sset->rand_fields().begin();
			f_it!=sset->rand_fields().end(); f_it++) {
		m_solver->initField(*f_it);
	}
	for (auto c_it=sset->constraints().begin();
			c_it!=sset->constraints().end(); c_it++) {
		m_solver->initConstraint(*c_it);
	}
}

} /* namespace vsc */

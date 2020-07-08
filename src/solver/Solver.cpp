
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
 * Solver.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "Solver.h"
#include "SolverBackendBoolector.h"

namespace vsc {

Solver::Solver(ISolverBackend *backend) : m_backend(backend) {
	// TODO Auto-generated constructor stub

}

Solver::~Solver() {
	// TODO Auto-generated destructor stub
}

bool Solver::randomize(
		uint64_t								seed,
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintBlockSP>	&constraints) {
	// First, analyze to determine which fields require solving,
	// and which do not
	ISolverInstUP solver_d(m_backend->createSolverInst());

	return true;
}

bool Solver::sat(
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintBlockSP>	&constraints) {
	return true;
}

Solver *Solver::inst() {
	if (!m_inst.get()) {
		m_inst = SolverUP(new Solver(new SolverBackendBoolector()));
	}

	return m_inst.get();
}

SolverUP Solver::m_inst;

} /* namespace vsc */

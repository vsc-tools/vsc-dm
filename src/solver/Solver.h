
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
 * Solver.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVER_H_
#define SRC_SOLVER_SOLVER_H_
#include <stdint.h>
#include <vector>
#include "Field.h"
#include "ConstraintBlock.h"
#include "ISolverBackend.h"

namespace vsc {

class Solver;
typedef std::unique_ptr<Solver> SolverUP;

class Solver {
public:
	Solver(ISolverBackend *backend);

	virtual ~Solver();

	virtual bool randomize(
			uint64_t								seed,
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints
			);

	virtual bool sat(
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints);

	static Solver *inst();

private:
	ISolverBackendUP			m_backend;
	static SolverUP				m_inst;
};


} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVER_H_ */

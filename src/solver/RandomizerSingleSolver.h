
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
 * RandomizerSingleSolver.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "datamodel/FieldScalar.h"
#include "solver/IRandomizer.h"
#include "solver/ISolverBackend.h"
#include "solver/RNG.h"
#include "solver/SolveGroup.h"
#include "solver/FieldBoundInfo.h"

namespace vsc {

class RandomizerSingleSolver : public IRandomizer {
public:
	RandomizerSingleSolver(
			uint32_t			seed,
			ISolverBackend 		*backend);

	virtual ~RandomizerSingleSolver();

	virtual bool randomize(
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintStmtSP>		&constraints);

private:

	virtual bool randomize_solvegroup(
			RNG					&rng,
			SolveGroup			*group);

	void swizzle_randvars(
			RNG					&rng,
			ISolverInstUP		&solver,
			SolveGroup			*group);

	ExprSP create_rand_domain_constraint(
			RNG					&rng,
			Field				*field,
			FieldBoundInfo		*info);

private:
	RNG									m_rng;
	ISolverBackendUP					m_backend;

};

} /* namespace vsc */


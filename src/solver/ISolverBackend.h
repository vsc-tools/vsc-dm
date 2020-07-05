
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
 * ISolverBackend.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_ISOLVERBACKEND_H_
#define SRC_SOLVER_ISOLVERBACKEND_H_
#include <memory>
#include <vector>
#include "ISolverData.h"
#include "ConstraintBlock.h"

namespace vsc {

class Field;

class ISolverBackend {
public:
	virtual ~ISolverBackend() { }

	// Get a solver instance
	virtual ISolverData *createSolverInst() = 0;

	// Creates solver data for a field
	virtual ISolverData *createFieldInst(
			ISolverData 		*solver,
			Field 				*f) = 0;

	// Creates solver data for a constraint
	virtual ISolverData* createConstraintInst(
			ISolverData			*solver,
			ConstraintBlock		*constraint) = 0;

	virtual void addAssume(
			ISolverData			*solver,
			ISolverData			*constraint) = 0;

	virtual void addAssert(
			ISolverData			*solver,
			ISolverData			*constraint) = 0;

	virtual bool failed(
			ISolverData			*solver,
			ISolverData			*constraint) = 0;

	virtual bool isSAT(ISolverData *solver) = 0;

};

typedef std::unique_ptr<ISolverBackend> ISolverBackendUP;

}




#endif /* SRC_SOLVER_ISOLVERBACKEND_H_ */

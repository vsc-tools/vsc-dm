
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
 * ISolverInst.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "solver/ISolverData.h"
#include "datamodel/Field.h"
#include "constraints/ConstraintStmt.h"

namespace vsc {

/**
 * Represents an instance of a backend solver
 */
class ISolverInst {
public:

	virtual ~ISolverInst() { }

	// Creates solver data for a field
	virtual void initField(Field *f) = 0;

	// Creates solver data for a constraint
	virtual void initConstraint(ConstraintStmt *c) = 0;

	virtual void addAssume(ConstraintStmt *c) = 0;

	virtual void addAssert(ConstraintStmt *c) = 0;

	virtual bool failed(ConstraintStmt *c) = 0;

	virtual bool isSAT() = 0;

	// Assign values to field
	virtual void finalizeField(Field *f) = 0;

};

typedef std::unique_ptr<ISolverInst> ISolverInstUP;

}




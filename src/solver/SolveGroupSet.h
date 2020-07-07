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
 * SolveSet.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVEGROUPSET_H_
#define SRC_SOLVER_SOLVEGROUPSET_H_
#include <vector>
#include "SolveGroup.h"
#include "datamodel/Field.h"

namespace vsc {

/**
 * A SolveSet captures relational information about a set of
 * constraints and fields being solved together
 *
 */
class SolveGroupSet {
public:
	SolveGroupSet();

	virtual ~SolveGroupSet();

	const std::vector<SolveGroupUP> &solvegroups() const {
		return m_solvegroups;
	}

	const std::vector<Field *> &unconstrained() const {
		return m_unconstrained;
	}

	void addSolveGroup(SolveGroup *g) {
		m_solvegroups.push_back(SolveGroupUP(g));
	}

	void addUnconstrained(Field *f) {
		m_unconstrained.push_back(f);
	}

private:
	std::vector<SolveGroupUP>				m_solvegroups;
	std::vector<Field *>					m_unconstrained;

};

} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVEGROUPSET_H_ */

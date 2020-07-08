
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
 * SolveGroup.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVEGROUP_H_
#define SRC_SOLVER_SOLVEGROUP_H_
#include <memory>
#include <set>
#include "datamodel/Field.h"

namespace vsc {

/**
 * A SolveGroup captures a set of related fields and
 * constraints
 */
class SolveGroup {
public:
	SolveGroup();

	virtual ~SolveGroup();

	const std::set<Field *> &fields() const {
		return m_field_s;
	}

	const std::set<ConstraintStmt *> &constraints() const {
		return m_constraint_s;
	}

	bool addConstraint(ConstraintStmt *c) {
		return m_constraint_s.insert(c).second;
	}

	bool addField(Field *f) {
		return m_field_s.insert(f).second;
	}

private:
	std::set<Field *>				m_field_s;
	std::set<ConstraintStmt *>		m_constraint_s;
};

typedef std::unique_ptr<SolveGroup> SolveGroupUP;

} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVEGROUP_H_ */

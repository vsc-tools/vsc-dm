
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
 * ConstraintScope.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTSCOPE_H_
#define SRC_CONSTRAINTS_CONSTRAINTSCOPE_H_
#include <vector>
#include "constraints/ConstraintStmt.h"

namespace vsc {

class ConstraintScope : public ConstraintStmt {
public:
	ConstraintScope();

	ConstraintScope(
			std::initializer_list<ConstraintStmt *> stmts);

	virtual ~ConstraintScope();

	const std::vector<ConstraintStmtSP> &constraints() const {
		return m_constraints;
	}

	void addConstraint(ConstraintStmt *c) {
		m_constraints.push_back(ConstraintStmtSP(c));
	}

	void addConstraint(ConstraintStmtSP c) {
		m_constraints.push_back(c);
	}

	virtual void accept(IVisitor *v) { v->visitConstraintScope(this); }

private:
	std::vector<ConstraintStmtSP>		m_constraints;
};

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTSCOPE_H_ */

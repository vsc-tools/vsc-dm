
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
 * SolveGroupSetBuilder.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#pragma once
#include <vector>
#include <set>
#include <map>
#include "VisitorBase.h"
#include "SolveGroupSet.h"
#include "Field.h"
#include "ConstraintBlock.h"

namespace vsc {

class SolveGroupSetBuilder : public VisitorBase {
public:
	SolveGroupSetBuilder();

	virtual ~SolveGroupSetBuilder();

	SolveGroupSet *build(
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintStmtSP>		&constraints
			);

	virtual void visitConstraintBlock(ConstraintBlock *c) override;

	virtual void visitConstraintStmtEnter(ConstraintStmt *c) override;

	virtual void visitConstraintStmtLeave(ConstraintStmt *c) override;

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

	virtual void visitFieldComposite(FieldComposite *f) override;

	virtual void visitFieldScalar(FieldScalar *f) override;

protected:

	void process_fieldref(Field *f);

private:
	uint32_t							m_pass;
	bool								m_used_rand;
	std::set<Field *>					m_field_s;
	ConstraintStmt						*m_active_constraint;
	SolveGroup							*m_active_solvegroup;
	std::set<SolveGroup *>				m_solvegroup_s;
	std::map<Field *, SolveGroup *>		m_field_solvegroup_m;
	std::vector<ConstraintStmt *>		m_constraint_l;
};

} /* namespace vsc */


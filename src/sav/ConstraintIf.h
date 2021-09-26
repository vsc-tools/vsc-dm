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
 * ConstraintIf.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#pragma once
#include "Expr.h"
#include "sav/ConstraintStmt.h"

namespace vsc {

class ConstraintIf : public ConstraintStmt {

public:
	ConstraintIf(
			Expr			*cond,
			ConstraintStmt	*true_s,
			ConstraintStmt	*false_s);

	ConstraintIf(
			ExprSP				cond,
			ConstraintStmtSP	true_s,
			ConstraintStmtSP	false_s);

	virtual ~ConstraintIf();

	Expr *cond() const { return m_cond.get(); }

	ConstraintStmt *true_s() const { return m_true_s.get(); }

	ConstraintStmt *false_s() const { return m_false_s.get(); }

	virtual void accept(IVisitor *v) { v->visitConstraintIf(this); }

private:
	ExprSP					m_cond;
	ConstraintStmtSP		m_true_s;
	ConstraintStmtSP		m_false_s;
};

} /* namespace vsc */


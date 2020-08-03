
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
 * SolverInstBoolector.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include <map>
#include "boolector/boolector.h"
#include "solver/ISolverInst.h"
#include "VisitorBase.h"

namespace vsc {

class SolverInstBoolector : public VisitorBase, public virtual ISolverInst {
public:
	SolverInstBoolector();

	virtual ~SolverInstBoolector();

	// Creates solver data for a field (and possibly sub-fields)
	virtual void initField(Field *f) override;

	// Creates solver data for a constraint
	virtual void initConstraint(ConstraintStmt *c) override;

	virtual void addAssume(ConstraintStmt *c) override;

	virtual void addAssert(ConstraintStmt *c) override;

	virtual bool failed(ConstraintStmt *c) override;

	virtual bool isSAT() override;

	virtual void finalizeField(Field *f) override;

	/**
	 * Visitor methods to support constraint construction
	 */

	virtual void visitConstraintExpr(ConstraintExpr *c) override;

	virtual void visitConstraintScope(ConstraintScope *c) override;

	virtual void visitExprBin(ExprBin *e) override;

	virtual void visitExprCond(ExprCond *e) override;

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

	virtual void visitExprValLiteral(ExprValLiteral *e) override;

	virtual void visitFieldScalar(FieldScalar *f) override;

private:
	enum SolverOp {
		Op_CreateField,
		Op_CreateConstraint,
		Op_FinalizeField
	};

private:

	void expr(Expr *e, BoolectorNode *&node, bool &is_signed, uint32_t &width);

	void mk_bool(BoolectorNode *&node, uint32_t &width);

	void resize(
			BoolectorNode		*&n1,
			bool				n1_is_signed,
			uint32_t			n1_width,
			BoolectorNode		*&n2,
			bool				n2_is_signed,
			uint32_t			n2_width);

	BoolectorSort get_sort(int32_t width);

private:
	Btor								*m_btor;
	SolverOp							m_op;

	// Temp data used by builders
	BoolectorNode						*m_node;
	bool								m_is_signed;

	std::map<uint32_t, BoolectorSort>	m_sort_m;

};

} /* namespace vsc */


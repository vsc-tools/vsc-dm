
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
 * ConstraintStmtExpr.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTEXPR_H_
#define SRC_CONSTRAINTS_CONSTRAINTEXPR_H_
#include "constraints/ConstraintStmt.h"
#include "expr/Expr.h"

namespace vsc {

class ConstraintExpr : public ConstraintStmt {
public:
	ConstraintExpr(Expr *expr);

	ConstraintExpr(ExprSP expr);

	virtual ~ConstraintExpr();

	Expr *expr() const { return m_expr.get(); }

	virtual void accept(IVisitor *v) { v->visitConstraintExpr(this); }

private:
	ExprSP				m_expr;
};

typedef std::shared_ptr<ConstraintExpr> ConstraintExprSP;

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTEXPR_H_ */

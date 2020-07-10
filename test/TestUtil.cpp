
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
 * TestUtil.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "TestUtil.h"

namespace vsc {

TestUtil::TestUtil() {
	// TODO Auto-generated constructor stub

}

TestUtil::~TestUtil() {
	// TODO Auto-generated destructor stub
}

vsc::ConstraintStmt *TestUtil::Constraint(
			vsc::Expr			*expr
			) {
	return new vsc::ConstraintExpr(expr);
}

vsc::Expr *TestUtil::Gt(FieldScalarSP field, uint64_t val) {
	return new vsc::ExprBin(
			new vsc::ExprFieldRef(field.get()),
			BinOp_Gt,
			new vsc::ExprNumericLiteral(
					ExprValNumericSP(new vsc::ExprValNumeric(val, 64, false)))
	);
}

vsc::Expr *TestUtil::Gt(Expr *lhs, Expr *rhs) {
	return new vsc::ExprBin(
			lhs,
			BinOp_Gt,
			rhs);
}

vsc::Expr *TestUtil::Lt(FieldScalarSP field, uint64_t val) {
	return new vsc::ExprBin(
			new vsc::ExprFieldRef(field.get()),
			BinOp_Lt,
			new vsc::ExprNumericLiteral(
					ExprValNumericSP(new ExprValNumeric(val, 64, false))));
}

vsc::Expr *TestUtil::Lt(Expr *lhs, Expr *rhs) {
	return new vsc::ExprBin(
			lhs,
			BinOp_Lt,
			rhs);
}

ConstraintIf *TestUtil::If(
		Expr									*cond,
		std::initializer_list<ConstraintStmt *>	true_s) {
	return new ConstraintIf(
			cond,
			new ConstraintScope(true_s),
			0);
}

ConstraintIf *TestUtil::If(
			Expr									*cond,
			std::initializer_list<ConstraintStmt *>	true_s,
			std::initializer_list<ConstraintStmt *>	false_s) {
	return new ConstraintIf(
			cond,
			new ConstraintScope(true_s),
			new ConstraintScope(false_s));
}

} /* namespace vsc */

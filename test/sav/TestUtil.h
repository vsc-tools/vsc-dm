
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
 * TestUtil.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "vsc.h"
#include <initializer_list>

namespace vsc {

class TestUtil {
public:
	TestUtil();
	virtual ~TestUtil();

	static uint64_t time_ms();

	static ConstraintStmt *Constraint(
			Expr				*expr
			);

	static ConstraintStmt *Soft(
			Expr				*expr
			);

	static Expr *Gt(
			FieldScalarSP		f,
			uint64_t			val);

	static Expr *Gt(
			Expr				*lhs,
			Expr				*rhs);

	static Expr *Lt(
			FieldScalarSP		f,
			uint64_t			val);

	static Expr *Lt(
			FieldScalarSP		f1,
			FieldScalarSP		f2);

	static Expr *Lt(
			Expr				*lhs,
			Expr				*rhs);

	static ConstraintIf *If(
			Expr									*cond,
			std::initializer_list<ConstraintStmt *>	true_s);

	static ConstraintIf *If(
			Expr									*cond,
			std::initializer_list<ConstraintStmt *>	true_s,
			std::initializer_list<ConstraintStmt *>	false_s);

};

} /* namespace vsc */


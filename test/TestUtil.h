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

	static ConstraintStmt *Constraint(
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


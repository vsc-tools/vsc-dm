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
			new vsc::ExprNumericLiteral(val));
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
			new vsc::ExprNumericLiteral(val));
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

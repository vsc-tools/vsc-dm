/*
 * TestModelExprEvaluator.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#include "TestModelExprEvaluator.h"
#include "ModelExprEvaluator.h"

namespace vsc {
using namespace facade;

TestModelExprEvaluator::TestModelExprEvaluator() {
	// TODO Auto-generated constructor stub

}

TestModelExprEvaluator::~TestModelExprEvaluator() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestModelExprEvaluator, smoke) {

	attr<ui_t<8>>		a {"a"};
	attr<ui_t<8>>		b {"b"};

	a(10);
	expr_base e = a;
	ModelExpr *a_expr = ctor::inst()->pop_expr();

	ModelVal val;
	a_expr->eval(val);

	ASSERT_EQ(val.val_u(), 10);
	ASSERT_EQ(val.bits(), 8);

}

TEST_F(TestModelExprEvaluator, bin_op_ult) {

	attr<ui_t<8>>		a {"a"};
	attr<ui_t<8>>		b {"b"};

	a(10);
	b(20);
	expr_base e = (a() < b());
	ModelExpr *expr = ctor::inst()->pop_expr();

	ModelVal val(64);
	expr->eval(val);

	ASSERT_EQ(val.val_u(), 1);
	ASSERT_EQ(val.bits(), 1);

}

} /* namespace vsc */

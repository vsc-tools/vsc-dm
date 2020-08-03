/*
 * TestConstraintExpr.cpp
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#include "TestConstraintExpr.h"
#include "TestUtil.h"

namespace vsc {

TestConstraintExpr::TestConstraintExpr() {
	// TODO Auto-generated constructor stub

}

TestConstraintExpr::~TestConstraintExpr() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestConstraintExpr, eq) {
	FieldSP a = FieldScalar::mk("a", 8, false, true);
	FieldSP b = FieldScalar::mk("b", 8, false, true);

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{a, b},
			{ConstraintExpr::mk(
					ExprBin::mk(
							ExprFieldRef::mk(a),
							BinOp_Eq,
							ExprFieldRef::mk(b)))}));
	if (!a->val()->eq(b->val())) {
		fprintf(stdout, "a=%lld b=%lld\n",
				static_cast<ExprValNumeric *>(a->val().get())->val_u(),
				static_cast<ExprValNumeric *>(b->val().get())->val_u());
	}
	ASSERT_TRUE(a->val()->eq(b->val()));
}

TEST_F(TestConstraintExpr, ne) {
	FieldSP a = FieldScalar::mk("a", 8, false, true);
	FieldSP b = FieldScalar::mk("b", 8, false, true);

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{a, b},
			{ConstraintExpr::mk(
					ExprBin::mk(
							ExprFieldRef::mk(a),
							BinOp_Ne,
							ExprFieldRef::mk(b)))}));
	if (!a->val()->ne(b->val())) {
		fprintf(stdout, "a=%lld b=%lld\n",
				static_cast<ExprValNumeric *>(a->val().get())->val_u(),
				static_cast<ExprValNumeric *>(b->val().get())->val_u());
	}
	ASSERT_TRUE(a->val()->ne(b->val()));
}

TEST_F(TestConstraintExpr, gt) {
	FieldSP a = FieldScalar::mk("a", 8, false, true);
	FieldSP b = FieldScalar::mk("b", 8, false, true);

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{a, b},
			{ConstraintExpr::mk(
					ExprBin::mk(
							ExprFieldRef::mk(a),
							BinOp_Gt,
							ExprFieldRef::mk(b)))}));
	if (!a->val()->ne(b->val())) {
		fprintf(stdout, "a=%lld b=%lld\n",
				static_cast<ExprValNumeric *>(a->val().get())->val_u(),
				static_cast<ExprValNumeric *>(b->val().get())->val_u());
	}
	ASSERT_GT(
			static_cast<ExprValNumeric *>(a->val().get())->val_u(),
			static_cast<ExprValNumeric *>(b->val().get())->val_u());
}

TEST_F(TestConstraintExpr, ge) {
	FieldSP a = FieldScalar::mk("a", 8, false, true);
	FieldSP b = FieldScalar::mk("b", 8, false, true);

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{a, b},
			{ConstraintExpr::mk(
					ExprBin::mk(
							ExprFieldRef::mk(a),
							BinOp_Ge,
							ExprFieldRef::mk(b)))}));
	if (!a->val()->ne(b->val())) {
		fprintf(stdout, "a=%lld b=%lld\n",
				static_cast<ExprValNumeric *>(a->val().get())->val_u(),
				static_cast<ExprValNumeric *>(b->val().get())->val_u());
	}
	ASSERT_GE(
			static_cast<ExprValNumeric *>(a->val().get())->val_u(),
			static_cast<ExprValNumeric *>(b->val().get())->val_u());
}

TEST_F(TestConstraintExpr, lt) {
	FieldSP a = FieldScalar::mk("a", 8, false, true);
	FieldSP b = FieldScalar::mk("b", 8, false, true);

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{a, b},
			{ConstraintExpr::mk(
					ExprBin::mk(
							ExprFieldRef::mk(a),
							BinOp_Lt,
							ExprFieldRef::mk(b)))}));
	if (!a->val()->ne(b->val())) {
		fprintf(stdout, "a=%lld b=%lld\n",
				static_cast<ExprValNumeric *>(a->val().get())->val_u(),
				static_cast<ExprValNumeric *>(b->val().get())->val_u());
	}
	ASSERT_LT(
			static_cast<ExprValNumeric *>(a->val().get())->val_u(),
			static_cast<ExprValNumeric *>(b->val().get())->val_u());
}

TEST_F(TestConstraintExpr, le) {
	FieldSP a = FieldScalar::mk("a", 8, false, true);
	FieldSP b = FieldScalar::mk("b", 8, false, true);

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{a, b},
			{ConstraintExpr::mk(
					ExprBin::mk(
							ExprFieldRef::mk(a),
							BinOp_Le,
							ExprFieldRef::mk(b)))}));
	ASSERT_LE(
			static_cast<ExprValNumeric *>(a->val().get())->val_u(),
			static_cast<ExprValNumeric *>(b->val().get())->val_u());
}

TEST_F(TestConstraintExpr, add) {
	FieldSP a = FieldScalar::mk("a", 8, false, true);
	FieldSP b = FieldScalar::mk("b", 8, false, true);
	FieldSP c = FieldScalar::mk("c", 8, false, true);

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{a, b, c},
			{
				ConstraintExpr::mk(
						ExprBin::mk(
								ExprFieldRef::mk(a),
								BinOp_Ne,
								ExprValLiteral::mk(ExprValNumeric::ZERO))),
				ConstraintExpr::mk(
						ExprBin::mk(
								ExprFieldRef::mk(a),
								BinOp_Lt,
								ExprValLiteral::mk(ExprValNumeric::mk(128, 8, false)))),
				ConstraintExpr::mk(
						ExprBin::mk(
								ExprFieldRef::mk(b),
								BinOp_Ne,
								ExprValLiteral::mk(ExprValNumeric::ZERO))),
				ConstraintExpr::mk(
						ExprBin::mk(
								ExprFieldRef::mk(b),
								BinOp_Lt,
								ExprValLiteral::mk(ExprValNumeric::mk(128, 8, false)))),
				ConstraintExpr::mk(
					ExprBin::mk(
							ExprFieldRef::mk(c),
							BinOp_Eq,
							ExprBin::mk(
									ExprFieldRef::mk(a),
									BinOp_Add,
									ExprFieldRef::mk(b))))}));
	ASSERT_EQ(
			static_cast<ExprValNumeric *>(c->val().get())->val_u(),
			(
					static_cast<ExprValNumeric *>(a->val().get())->val_u() +
					static_cast<ExprValNumeric *>(b->val().get())->val_u()));
}


} /* namespace vsc */

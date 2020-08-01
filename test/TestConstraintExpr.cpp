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
	FieldCompositeSP my_c(new FieldComposite("my_c", true));
	FieldSP a = my_c->addField(new FieldScalar("a", 8, false, true));
	FieldSP b = my_c->addField(new FieldScalar("b", 8, false, true));

	ASSERT_TRUE(RandomizerFactory::inst()->randomize(
			{my_c},
			{ConstraintBlock::mk({})}));

}

} /* namespace vsc */

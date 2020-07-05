/*
 * TestSmoke.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "TestSmoke.h"

#include "vsc.h"

namespace vsc {

TestSmoke::TestSmoke() {
	// TODO Auto-generated constructor stub

}

TestSmoke::~TestSmoke() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestSmoke, smoke) {
	fprintf(stdout, "Hello\n");
	vsc::FieldScalarSP a(new vsc::FieldScalar("a", 32, false, true));

	vsc::Solver *solver = Solver::inst();

	std::vector<FieldSP> fields = {a};
	std::vector<ConstraintBlockSP> constraints = {};

	solver->randomize(0, fields, constraints);
}

} /* namespace vsc */

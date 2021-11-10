/*
 * TestScalarVec.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#include "TestScalarVec.h"

namespace vsc {

using namespace facade;

TestScalarVec::TestScalarVec() {
	// TODO Auto-generated constructor stub

}

TestScalarVec::~TestScalarVec() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestScalarVec, smoke) {

	class my_c : public rand_obj {
	public:

		my_c(const scope &s) : rand_obj(this) { }

		rand_vec<ui_t<8>>			arr {"arr"};
	};

	my_c c("c");

	ASSERT_EQ(c.arr.size(), 0);
	c.arr.push_back(0);
	ASSERT_EQ(c.arr.size(), 1);
	c.arr.push_back(1);
	ASSERT_EQ(c.arr.size(), 2);

	ASSERT_TRUE(c.randomize());

	for (uint32_t i=0; i<c.arr.size(); i++) {
		fprintf(stdout, "data[%d] %lld\n", i, c.arr[i]());
	}

}

} /* namespace vsc */

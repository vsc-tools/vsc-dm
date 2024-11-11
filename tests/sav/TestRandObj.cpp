/*
 * TestRandObj.cpp
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#include "TestRandObj.h"

namespace vsc {

TestRandObj::TestRandObj() {
	// TODO Auto-generated constructor stub

}

TestRandObj::~TestRandObj() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestRandObj, decl) {

	class my_c : public rand_obj {
	public:

		my_c(const scope &s) : rand_obj(this) {

		}

		attr<int>		a{{this, "a"}};

		constraint ab_c{this, [&] {
			a == 1;

			if_then(expr_base(), [&] {

			}).else_then([&] {

			});
		}};
	};

	my_c c1("abc");
}

} /* namespace vsc */

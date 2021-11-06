/*
 * TestInside.cpp
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#include "TestInside.h"


namespace vsc {
using namespace facade;

TestInside::TestInside() {
	// TODO Auto-generated constructor stub

}

TestInside::~TestInside() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestInside, single) {

	class my_s : public rand_obj {
	public:
		my_s(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>			a { "a" };
		rand_attr<ui_t<8>>			b { "b" };
		rand_attr<ui_t<8>>			c { "c" };
		rand_attr<ui_t<8>>			d { "d" };

		constraint ab_c { "ab_c", [&] {
			inside(a, {1, 2, 4, 8});

			c != 0;
			d != 0;

			c < d;

			inside(b, { {c, d} });
		}};
	};
}

} /* namespace vsc */

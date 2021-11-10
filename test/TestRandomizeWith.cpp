/*
 * TestRandomizeWith.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#include "TestRandomizeWith.h"

namespace vsc {

using namespace facade;

TestRandomizeWith::TestRandomizeWith() {
	// TODO Auto-generated constructor stub

}

TestRandomizeWith::~TestRandomizeWith() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestRandomizeWith, smoke) {

	class my_class : public rand_obj {
	public:

		my_class(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>			a {"a"};
		rand_attr<ui_t<16>>			b {"b"};
		rand_attr<ui_t<16>>			c {"c"};
		rand_attr<ui_t<16>>			d {"d"};

		constraint my_a_c {"my_a_c", [&] {
			a < 10;
			if_then(a == 2, [&] {
				b < 1000;
			}).else_then([&] {
				b < 2000;
			});
		}};
	};

	my_class c("c");

	for (uint32_t i=0; i<1000; i++) {
		ASSERT_TRUE(c.randomize_with([&] {
			c.a == (i%10);
		}));

		ASSERT_EQ(c.a(), (i%10));
		if ((i%10) == 2) {
			ASSERT_LT(c.b(), 1000);
		} else {
			ASSERT_LT(c.b(), 2000);
		}
	}

}

} /* namespace vsc */

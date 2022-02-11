/*
 * TestNestedClasses.cpp
 *
 *  Created on: Feb 7, 2022
 *      Author: mballance
 */

#include "TestNestedClasses.h"
#include "vsc_facade.h"

namespace vsc {

using namespace facade;

TestNestedClasses::TestNestedClasses() {
	// TODO Auto-generated constructor stub

}

TestNestedClasses::~TestNestedClasses() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestNestedClasses, smoke) {

	class C1 : public rand_obj {
	public:
		C1(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>			a {"a"};
	};

	class C2 : public rand_obj {
	public:
		C2(const scope &s) : rand_obj(this) { }

		rand_attr<C1>				b {"b"};
	};

	attr<C2> f("f");
	f->b->a(5);
	ASSERT_EQ(f->b->a(), 5);
	f->b->a = 4;
	ASSERT_EQ(f->b->a(), 4);
	fprintf(stdout, "a=%d\n", f->b->a());
}

} /* namespace vsc */

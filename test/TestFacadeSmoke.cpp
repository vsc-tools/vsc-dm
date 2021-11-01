/*
 * TestFacadeSmoke.cpp
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#include "TestFacadeSmoke.h"
#include "ctor.h"

using namespace vsc::facade;

namespace vsc {

TestFacadeSmoke::TestFacadeSmoke() {
	// TODO Auto-generated constructor stub

}

TestFacadeSmoke::~TestFacadeSmoke() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestFacadeSmoke, smoke) {
	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<int>			a {"a"};
		rand_attr<int>			b {"b"};
	};

	MyC c("a");

}

TEST_F(TestFacadeSmoke, smoke_inh) {

	class MyBase : public rand_obj {
	public:
		MyBase(const scope &s) : rand_obj(this) { }

		rand_attr<int>			base_a {"base_a"};
		rand_attr<int>			base_b {"base_b"};
	};

	class MyC : public MyBase {
	public:
		MyC(const scope &s) : MyBase(this) { }

		rand_attr<int>			a {"a"};
		rand_attr<int>			b {"b"};
	};

	MyC c("a");

}

TEST_F(TestFacadeSmoke, smoke_inh_attr) {

	class MyBase : public rand_obj {
	public:
		MyBase(const scope &s) : rand_obj(this) { }

		rand_attr<int>			base_a {"base_a"};
		rand_attr<int>			base_b {"base_b"};
	};

	class MyC : public MyBase {
	public:
		MyC(const scope &s) : MyBase(this) { }

		rand_attr<int>			a {"a"};
		rand_attr<int>			b {"b"};
		rand_attr<unsigned int>	c {"c"};

		constraint				ab_c {"ab_c", [this] {
			a == b;
			b == c;
		}};
	};


	class MyC2 : public rand_obj {
	public:
		MyC2(const scope &s) : rand_obj(this) { }

		rand_attr<MyC>			a {"a"};
		rand_attr<int>			b {"b"};
	};

	MyC2 c("c");

	ASSERT_EQ(c.fullname(), "c");
	ASSERT_EQ(c.b.fullname(), "c.b");
	ASSERT_EQ(c.a.b.fullname(), "c.a.b");

	c.randomize();
}

TEST_F(TestFacadeSmoke, constraint_inh) {

	class MyBase : public rand_obj {
	public:
		MyBase(const scope &s) : rand_obj(this) { }

		rand_attr<int>			base_a {"base_a"};
		rand_attr<int>			base_b {"base_b"};

		constraint				ab_c {"ab_c", [&] {
			fprintf(stdout, "ab_c\n");
			base_a == base_b;
		}};
	};

	class MyC : public MyBase {
	public:
		MyC(const scope &s) : MyBase(this) { }

		rand_attr<int>			a {"a"};
		rand_attr<int>			b {"b"};
		rand_attr<unsigned int>	c {"c"};

		constraint				ab_c {"ab_c", [&] {
			fprintf(stdout, "ab_c\n");
			a == c;
		}};
	};

	MyC c("z");

}

TEST_F(TestFacadeSmoke, constraint_expr) {

	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<int>			a {"a"};
		rand_attr<int>			b {"b"};
		rand_attr<unsigned int>	c {"c"};

		constraint				ab_c {"ab_c", [&] {
			a != c;
		}};
	};

	MyC c("c");

	for (uint32_t i=0; i<1000; i++) {
		c.randomize();
	}

}

TEST_F(TestFacadeSmoke, constraint_expr_literal) {

	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<si_t<8>>		ia {"ia"};
		rand_attr<ui_t<32>>		ib {"ib"};
		rand_attr<ui_t<8>>		a {"a"};
		rand_attr<ui_t<8>>		b {"b"};
		rand_attr<ui_t<8>>		c {"c"};

		attr<ui_t<8>>			d {"d", 5};

		constraint				ab_c {"ab_c", [&] {
			a == si_t<8>(1);
			b == si_t<8>(2);
			c == d;
		}};
	};

	MyC c("c");

	ASSERT_TRUE(c.randomize());
	ASSERT_EQ(c.a(), 1);
	ASSERT_EQ(c.b(), 2);
	ASSERT_EQ(c.c(), 5);
	/*
	 */
}

TEST_F(TestFacadeSmoke, constraint_if_else) {

	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<si_t<8>>		ia {"ia"};
		rand_attr<ui_t<32>>		ib {"ib"};
		rand_attr<ui_t<8>>		a {"a"};
		rand_attr<ui_t<8>>		b {"b"};
		rand_attr<ui_t<8>>		c {"c"};

		attr<ui_t<8>>			d {"d", 5};

		constraint				ab_c {"ab_c", [&] {
			if_then(d == 5, [&] {
				a < 10;
				b > 10;
			}).else_then([&] {
				a > 10;
				b < 10;
			});
			c == d;
		}};
	};

	MyC c("c");

	ASSERT_TRUE(c.randomize());
	ASSERT_LT(c.a(), 10);
	ASSERT_GT(c.b(), 10);
	ASSERT_EQ(c.c(), 5);
	/*
	 */
}

} /* namespace vsc */
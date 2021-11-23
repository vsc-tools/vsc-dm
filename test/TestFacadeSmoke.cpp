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

#ifdef UNDEFINED
TEST_F(TestFacadeSmoke, smoke) {
	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<int>			a {"a"};
		rand_attr<int>			b {"b"};
	};

	MyC c("a");

}
#endif

TEST_F(TestFacadeSmoke, attr_assign) {
	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>		a {"a"};
		rand_attr<ui_t<8>>		b {"b"};
	};

	attr<MyC> c("c");

	c->a = 5;
	c->b = 7;
	ASSERT_EQ(c->a, 5);
	ASSERT_EQ(c->b, 7);

	c->a = c->b;
	ASSERT_EQ(c->a, 7);
	ASSERT_EQ(c->b, 7);
}

TEST_F(TestFacadeSmoke, attr_assign_2) {
	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>		a {"a"};
		rand_attr<ui_t<10>>		b {"b"};
	};

	attr<MyC> c("c");

	c->a = 5;
	c->b = 7;
	ASSERT_EQ(c->a, 5);
	ASSERT_EQ(c->b, 7);

	c->a = c->b;
	ASSERT_EQ(c->a, 7);
	ASSERT_EQ(c->b, 7);
}

TEST_F(TestFacadeSmoke, attr_assign_3) {
	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>		a {"a"};
		rand_attr<si_t<10>>		b {"b"};
	};

	attr<MyC> c("c");

	c->a = 5;
	c->b = 7;
	ASSERT_EQ(c->a, 5);
	ASSERT_EQ(c->b, 7);

	c->a = c->b;
	ASSERT_EQ(c->a, 7);
	ASSERT_EQ(c->b, 7);

	fprintf(stdout, "a=%lld\n",
			(int64_t)c->a);
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

	attr<MyC> c("a");

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
			a() == b();
			b() == c();
		}};
	};


	class MyC2 : public rand_obj {
	public:
		MyC2(const scope &s) : rand_obj(this) { }

		rand_attr<MyC>			a {"a"};
		rand_attr<int>			b {"b"};
	};

	attr<MyC2> c("c");

	ASSERT_EQ(c->fullname(), "c");
	ASSERT_EQ(c->b->fullname(), "c.b");
	ASSERT_EQ(c->a->b->fullname(), "c.a.b");

	c->randomize();
}

TEST_F(TestFacadeSmoke, constraint_inh) {

	class MyBase : public rand_obj {
	public:
		MyBase(const scope &s) : rand_obj(this) { }

		rand_attr<int>			base_a {"base_a"};
		rand_attr<int>			base_b {"base_b"};

		constraint				ab_c {"ab_c", [&] {
			fprintf(stdout, "ab_c\n");
			base_a() == base_b();
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
			a() == c();
		}};
	};

	attr<MyC> c("z");

}
#ifdef UNDEFINED
#endif

TEST_F(TestFacadeSmoke, constraint_expr) {

	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>		a {"a"};
		rand_attr<ui_t<8>>		b {"b"};
		rand_attr<ui_t<8>>		c {"c"};

		constraint				ab_c {"ab_c", [&] {
			a() != 0; // ui_t<8>(0);
			c() != 0; // ui_t<8>(0);
			b() != 0; // ui_t<8>(0);
			a() != c();
		}};
	};

	attr<MyC> c("c");

	for (uint32_t i=0; i<1000; i++) {
		c->randomize();
		ASSERT_NE(c->a, 0);
		ASSERT_NE(c->b, 0);
		ASSERT_NE(c->c, 0);
		ASSERT_NE(c->a, c->c);
	}

}

#ifdef UNDEFINED
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

TEST_F(TestFacadeSmoke, constraint_foreach_unroll) {

	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }
		rand_attr<ui_t<13>>		lead {"lead"};
		rand_attr<ui_t<13>>		shared0 {"shared0"};
		rand_attr<ui_t<13>>		shared1 {"shared1"};
		rand_attr<ui_t<13>>		shared2 {"shared2"};
		rand_attr<ui_t<13>>		shared3 {"shared3"};
		rand_attr<ui_t<13>>		shared4 {"shared4"};
		rand_attr<ui_t<13>>		shared5 {"shared5"};
		rand_attr<ui_t<13>>		shared6 {"shared6"};
		rand_attr<ui_t<13>>		shared7 {"shared7"};
		rand_attr<ui_t<13>>		side_effect0 {"side_effect0"};
		rand_attr<ui_t<13>>		side_effect1 {"side_effect1"};
		rand_attr<ui_t<13>>		side_effect2 {"side_effect2"};
		rand_attr<ui_t<13>>		side_effect3 {"side_effect3"};
		rand_attr<ui_t<13>>		side_effect4 {"side_effect4"};
		rand_attr<ui_t<13>>		side_effect5 {"side_effect5"};
		rand_attr<ui_t<13>>		side_effect6 {"side_effect6"};
		rand_attr<ui_t<13>>		side_effect7 {"side_effect7"};

		constraint				ab_c {"ab_c", [&] {
			if_then(shared0 == lead, [&] {
				side_effect0 == shared0;
			}).else_then([&] {
				(side_effect0 > shared0) && (side_effect0 < lead);
			});
			if_then(shared1 == shared0, [&] {
				side_effect1 == shared1;
			}).else_then([&] {
				(side_effect1 > shared1) && (side_effect1 < shared0);
			});
			if_then(shared2 == shared1, [&] {
				side_effect2 == shared2;
			}).else_then([&] {
				(side_effect2 > shared2) && (side_effect2 < shared1);
			});
			if_then(shared3 == shared2, [&] {
				side_effect3 == shared3;
			}).else_then([&] {
				(side_effect3 > shared3) && (side_effect3 < shared2);
			});
			if_then(shared4 == shared3, [&] {
				side_effect4 == shared4;
			}).else_then([&] {
				(side_effect4 > shared4) && (side_effect4 < shared3);
			});
			if_then(shared5 == shared4, [&] {
				side_effect5 == shared5;
			}).else_then([&] {
				(side_effect5 > shared5) && (side_effect5 < shared4);
			});
			if_then(shared6 == shared5, [&] {
				side_effect6 == shared6;
			}).else_then([&] {
				(side_effect6 > shared6) && (side_effect6 < shared5);
			});
			if_then(shared7 == shared6, [&] {
				side_effect7 == shared7;
			}).else_then([&] {
				(side_effect7 > shared7) && (side_effect7 < shared6);
			});
		}};
	};

	MyC c("c");

	for (uint32_t i=0; i<1000; i++) {
		ASSERT_TRUE(c.randomize());
		/*
		fprintf(stdout, "0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",
				c.shared0(), c.shared1(), c.shared2(), c.shared3(),
				c.shared4(), c.shared5(), c.shared6(), c.shared7());
		fprintf(stdout, "0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",
				c.side_effect0(), c.side_effect1(), c.side_effect2(), c.side_effect3(),
				c.side_effect4(), c.side_effect5(), c.side_effect6(), c.side_effect7());
		 */
	}
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

TEST_F(TestFacadeSmoke, enum_type_field) {

	enum my_e {
		A,
		B,
		C,
		D,
		E,
		F
	};

	using my_e_t=enum_t<my_e, A, F>;

	class MyC : public rand_obj {
	public:
		MyC(const scope &s) : rand_obj(this) { }

		rand_attr<my_e_t>		ia {"ia"};
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
#endif

} /* namespace vsc */

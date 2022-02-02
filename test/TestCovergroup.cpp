/*
 * TestCovergroup.cpp
 *
 *  Created on: Nov 9, 2021
 *      Author: mballance
 */

#include "TestCovergroup.h"

namespace vsc {

using namespace facade;

TestCovergroup::TestCovergroup() {
	// TODO Auto-generated constructor stub

}

TestCovergroup::~TestCovergroup() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestCovergroup, simple_coverpoint) {

	class my_covergroup : public covergroup {
	public:
		my_covergroup(const scope &s) : covergroup(this) { }

		// Sampling method
		with_sample<ui_t<4>> sample;

		coverpoint cp1 { "cp1", std::get<0>(sample.items), [&] {
			bins abc { "abc", {1, {2,5}} };
		}};
		coverpoint cp2 { "cp2", std::get<0>(sample.items),
						iff(std::get<0>(sample.items)() < 10), [&] {
			bins abc { "abc", {1, {2,5}} };
		}};
	};

	my_covergroup cg("cg");

	cg.sample(5);
	cg.sample(10);
}

TEST_F(TestCovergroup, simple_coverpoint_autobins) {

	class my_covergroup : public covergroup {
	public:
		my_covergroup(const scope &s) : covergroup(this) { }

		// Sampling method
		with_sample<ui_t<4>> sample;

		coverpoint cp1 { "cp1", std::get<0>(sample.items), [&] {
//			bins abc { "abc" };
		}};
	};

	my_covergroup cg("cg");

	cg.sample(5);
	cg.sample(10);
}

TEST_F(TestCovergroup, simple_coverpoint_inf_array_bins) {

	class my_covergroup : public covergroup {
	public:
		my_covergroup(const scope &s) : covergroup(this) { }

		// Sampling method
		with_sample<ui_t<4>> sample;

		coverpoint cp1 { "cp1", std::get<0>(sample.items)(), [&] {
			bins abc { "abc", {}, { {1, 7} } };
		}};
	};

	my_covergroup cg("cg");

	cg.sample(5);
	cg.sample(10);
}

TEST_F(TestCovergroup, simple_coverpoint_sz_array_bins) {

	class my_covergroup : public covergroup {
	public:
		my_covergroup(const scope &s) : covergroup(this) { }

		// Sampling method
		with_sample<ui_t<4>> sample;

		coverpoint cp1 { "cp1", std::get<0>(sample.items)(), [&] {
			bins abc { "abc", {4}, { {1, 7} } };
		}};
	};

	my_covergroup cg("cg");

	cg.sample(5);
	cg.sample(10);
}

TEST_F(TestCovergroup, simple_cross) {

	class my_covergroup : public covergroup {
	public:
		my_covergroup(const scope &s) : covergroup(this) {
			options.at_least = 2;
		}

		// Sampling method
		with_sample<ui_t<4>,ui_t<4>> sample;

		coverpoint cp1 { "cp1", std::get<0>(sample.items)(), [&] {
			bins abc { "abc", {1, {2,3}} };
		}};
		coverpoint cp2 { "cp2", std::get<1>(sample.items)(), [&] {
			bins abc { "abc", {1, {2,3}} };
		}};
		cross cr {"cr", {cp1, cp2}};
	};
}

TEST_F(TestCovergroup, simple_coverpoint_options) {

	class my_covergroup : public covergroup {
	public:
		my_covergroup(const scope &s) : covergroup(this) { }

		// Sampling method
		with_sample<ui_t<4>> sample;

		coverpoint cp1 { "cp1", std::get<0>(sample.items)(), [&](options_t &options) {
			options.auto_bin_max = 4;
		}};

	};
}

} /* namespace vsc */

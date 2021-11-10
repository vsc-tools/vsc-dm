/*
 * covergroup.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include "attr.h"
#include "ctor.h"
#include "expr_range.h"
#include "rand_obj.h"
#include <vector>

namespace vsc {
namespace facade {

class covergroup : public rand_obj {
public:
	covergroup(const scope &s);

	virtual ~covergroup();

	virtual void sample();

	struct options_t {
		uint32_t			weight = 1;
		uint32_t			goal = 100;
		std::string			comment;
		uint32_t			at_least = 1;
		uint32_t			auto_bin_max = 64;
	};

	// TODO: need a new container class -- rand_obj is too specific
	template <class ...T> class with_sample : public rand_obj {
	public:
		std::tuple<attr<T>...>	items;

		covergroup *cg;

		with_sample(const scope &s="") : rand_obj(this) {
			cg = static_cast<covergroup *>(ctor::inst()->scope());
			// TODO: construct items-tuple items

			// Items are children of this scope
		}

		void operator ()(T... args) {
			// TODO: set the value of items-tuple items

			// Call the base sample method to perform the
			// actual sampling
			cg->sample();
		}
	};

	class coverpoint {
	public:
		coverpoint(
			const scope						&name,
			const expr_base					&expr,
			const std::function<void()>		&body);

		coverpoint(
			const scope								&name,
			const expr_base							&expr,
			const std::function<void(options_t &)>	&body);

	private:
		std::function<void()>				m_body;
		std::function<void(options_t &)>	m_body_opts;

	};

	// Wrapper to enable referencing coverpoints by ref
	class cp_ref {
	public:
		cp_ref(const coverpoint &cp);
	};

	class cross {
	public:
		cross(
			const scope						&s,
			const std::vector<cp_ref>		&terms);
	};

	class bins {
	public:
		bins(
			const scope 					&s,
			const std::vector<expr_range>	&ranges);
	};

	class ignore_bins {
	public:
		ignore_bins(
			const scope 					&s,
			const std::vector<expr_range>	&ranges);
	};

	class illegal_bins {
	public:
		illegal_bins(
			const scope 					&s,
			const std::vector<expr_range>	&ranges);
	};

protected:
	options_t				options;

};

#ifdef UNDEFINED
class my_covergroup : public covergroup {
public:

	my_covergroup(const scope &s) : covergroup(this) { }

	virtual ~my_covergroup() { }

	// Need a function-like object that accepts
	// some arguments
	with_sample<ui_t<8>,ui_t<16>,si_t<32>> sample {this};

};


void doit() {
	my_covergroup c("cg");
	c.sample(5, 6, 7);
	std::get<0>(c.sample.items).fullname();
	std::get<0>(c.sample.items) = 2;
}
#endif

} /* namespace facade */
} /* namespace vsc */


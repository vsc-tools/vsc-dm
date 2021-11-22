/*
 * covergroup.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include <functional>
#include <stdio.h>
#include <vector>
#include "attr.h"
#include "ctor.h"
#include "expr_range.h"
#include "obj_scope.h"
#include "ModelValRangelist.h"

namespace vsc {
namespace facade {

class covergroup : public obj_scope {
public:
	covergroup(const scope &s);

	virtual ~covergroup();

	virtual void sample();

	virtual void build() override;

	struct options_t {
		uint32_t			weight = 1;
		uint32_t			goal = 100;
		std::string			comment;
		uint32_t			at_least = 1;
		uint32_t			auto_bin_max = 64;
	};

	class with_sample_base : public obj_scope {
	public:
		with_sample_base(const scope &s);

		virtual void build() override;

	protected:
		covergroup				*m_cg;
		ModelFieldRoot			*m_field;
	};

	// Several coverage elements are scopes containing field instances
	// - covergroup with cross/coverpoint sub-fields
	// - with_sample with sub-fields to be sampled for coverage
	//
	// TODO: need a new container class -- rand_obj is too specific
	template <class ...T> class with_sample : public with_sample_base {
	public:

		with_sample() : with_sample_base("sample") {
			// TODO: construct items-tuple items

			// Set the name of scope items svar0..svarN-1
			_setname(items);
		}

		void operator ()(T const &... args) {
			// Set the value of the coverage-sampling fields
			_setval(items, args...);

			// Call the base sample method to perform the
			// actual sampling. Coverpoint references are
			// with respect to the fields already
			m_cg->sample();
		}

		// Sample-method fields to be used by coverpoints
		std::tuple<attr<T>...>	items;

	private:

		/**
		 * Proxy classes used to propagate values from the sample-method
		 * parameters to the item elements on which coverage is defined
		 */
		template <size_t I=0, class... Ts>
			typename std::enable_if<(I==sizeof...(Ts)), void>::type
				_setval(std::tuple<attr<Ts>...> &tup) { }
		template <size_t I=0, class... Ts, class PT, class... PTs>
			typename std::enable_if<(I<sizeof...(Ts)), void>::type
			   _setval(std::tuple<attr<Ts>...> &tup, PT const &first, PTs const&... rest) {
			std::get<I>(tup)(first);
		    _setval<I+1>(tup, rest...);
		}

		/**
		 * Proxy classes used to assign a unique name to each sample field
		 */
		template <size_t I=0, class... Ts>
			typename std::enable_if<(I==sizeof...(Ts)), void>::type
				_setname(std::tuple<attr<Ts>...> &tup) { }
		template <size_t I=0, class... Ts>
			typename std::enable_if<(I<sizeof...(Ts)), void>::type
			   _setname(std::tuple<attr<Ts>...> &tup) {
			char tmp[64];
			sprintf(tmp, "svar%d", I);
			std::get<I>(tup).name(tmp);
		    _setname<I+1>(tup);
		}
	};

	struct iff {
		iff(const expr_base &e) {
			ctor::inst()->pop_expr();
			m_iff = e.core();
		}
		ModelExpr			*m_iff;
	};

	class bins;
	class ignore_bins;
	class illegal_bins;
	class coverpoint : public obj {
	public:
		coverpoint(
			const scope						&name,
			const expr_base					&expr,
			const std::function<void()>		&body);

		coverpoint(
			const scope						&name,
			const expr_base					&expr,
			const iff						&iff_e,
			const std::function<void()>		&body);

		coverpoint(
			const scope								&name,
			const expr_base							&expr,
			const std::function<void(options_t &)>	&body);

		coverpoint(
			const scope								&name,
			const expr_base							&expr,
			const iff								&iff_e,
			const std::function<void(options_t &)>	&body);

		coverpoint &iff(const expr_base &expr);

		void add_bins(bins *b);

		void add_ignore_bins(ignore_bins *b);

		void add_illegal_bins(illegal_bins *b);

		double get_coverage();

		virtual void build() override;

	private:
		ModelCoverpoint						*m_cp;
		ModelExpr							*m_target;
		ModelExpr							*m_iff;
		std::function<void()>				m_body;
		std::function<void(options_t &)>	m_body_opts;
		std::vector<bins *>					m_bins;
		std::vector<ignore_bins *>			m_ignore_bins;
		std::vector<illegal_bins *>			m_illegal_bins;
	};

	// Wrapper to enable referencing coverpoints by ref
	struct cp_ref {
		cp_ref(const coverpoint &cp) : m_cp(&cp) { }
		const coverpoint		*m_cp;
	};

	class cross : public obj {
	public:
		cross(
			const scope						&s,
			const std::vector<cp_ref>		&terms);

		virtual void build() override;

	private:
		std::vector<const coverpoint *>		m_terms;
	};

	class bins {
	public:
		bins(
			const std::string				&name,
			const std::vector<expr_range>	&ranges);

		bins(
			const std::string				&name,
			const expr_base					&sz,
			const std::vector<expr_range>	&ranges);

		std::string							m_name;
		bool								m_is_array;
		int32_t								m_n_bins;
		ModelValRangelist					m_ranges;

	};

	class ignore_bins {
	public:
		ignore_bins(
			const std::string				&name,
			const std::vector<expr_range>	&ranges);

		std::string							m_name;
		ModelValRangelist					m_ranges;

	};

	class illegal_bins {
	public:
		illegal_bins(
			const std::string				&name,
			const std::vector<expr_range>	&ranges);

		std::string							m_name;
		ModelValRangelist					m_ranges;

	};

protected:
	void add_coverpoint(coverpoint *cp);

	void add_cross(cross *cr);


protected:
	options_t				options;

private:
	std::vector<coverpoint *>		m_coverpoints;
	std::vector<cross *>			m_crosses;

};

} /* namespace facade */
} /* namespace vsc */


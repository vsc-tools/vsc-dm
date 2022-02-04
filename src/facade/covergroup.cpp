/*
 * covergroup.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#include "covergroup.h"
#include "ctor.h"
#include "Debug.h"
#include "ModelCoverpoint.h"
#include "ModelExprEvaluator.h"

#undef EN_DEBUG_COVERGROUP

#ifdef EN_DEBUG_COVERGROUP
DEBUG_SCOPE(covergroup);
#define DEBUG_ENTER(fmt, ...) \
	DEBUG_ENTER_BASE(covergroup, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
	DEBUG_LEAVE_BASE(covergroup, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
	DEBUG_BASE(covergroup, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {
namespace facade {

covergroup::covergroup(const scope &s) :
		obj_scope(ObjType_Covergroup|ObjType_Scope) {
	// TODO Auto-generated constructor stub

}

covergroup::~covergroup() {
	// TODO Auto-generated destructor stub
}

void covergroup::sample() {
	DEBUG_ENTER("sample");
	DEBUG_LEAVE("sample");
}

void covergroup::build() {
	DEBUG_ENTER("build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
	if (ctor::inst()->build_phase() == 0) {
		m_cg = ModelCovergroupUP(new ModelCovergroup());
		m_cg->options().weight(options.weight);
		m_cg->options().goal(options.goal);
		m_cg->options().comment(options.comment);
		m_cg->options().at_least(options.at_least);
		m_cg->options().auto_bin_max(options.auto_bin_max);
	}
	obj_scope::build();
	DEBUG_LEAVE("build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
}

covergroup::with_sample_base::with_sample_base(const scope &s) :
		obj_scope(ObjType_CoverSample|ObjType_Scope), m_field(0) {
	m_cg = static_cast<covergroup *>(ctor::inst()->scope());
}

void covergroup::with_sample_base::build() {
	DEBUG_ENTER("with_sample::build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
	if (ctor::inst()->build_phase() == 0) {
		// Only build out cover samples
		for (auto it=children().begin(); it!=children().end(); it++) {
			if ((*it)->is_type(ObjType_CoverSample)) {
				(*it)->build();
			}
		}
	} else if (ctor::inst()->build_phase() == 1) {
		// Only build out coverpoints
		for (auto it=children().begin(); it!=children().end(); it++) {
			if ((*it)->is_type(ObjType_Coverpoint)) {
				(*it)->build();
			}
		}
	} else if (ctor::inst()->build_phase() == 2) {
		// Only build out cross points
		for (auto it=children().begin(); it!=children().end(); it++) {
			if ((*it)->is_type(ObjType_CoverCross)) {
				(*it)->build();
			}
		}
	}
	DEBUG_LEAVE("with_sample::build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
}

covergroup::coverpoint::coverpoint(
		const scope					&name,
		const expr_base				&expr,
		const std::function<void()>	&body) : obj(ObjType_Coverpoint),
				m_cp(0), m_iff(0), m_body(body) {
	// Pop the sample expression
	ctor::inst()->pop_expr();
	m_target = expr.core();
}

covergroup::coverpoint::coverpoint(
		const scope					&name,
		const expr_base				&expr,
		const covergroup::iff		&iff_e,
		const std::function<void()>	&body) : obj(ObjType_Coverpoint),
				m_cp(0), m_iff(0), m_body(body) {
	// Pop the sample expression
	ctor::inst()->pop_expr();
	m_target = expr.core();
	m_iff = iff_e.m_iff;
}

covergroup::coverpoint::coverpoint(
		const scope											&name,
		const expr_base										&expr,
		const std::function<void(covergroup::options_t &)>	&body) :
			obj(ObjType_Coverpoint), m_cp(0), m_iff(0), m_body_opts(body) {

	// Pop the sample expression
	ctor::inst()->pop_expr();
	m_target = expr.core();
}

covergroup::coverpoint::coverpoint(
		const scope											&name,
		const expr_base										&expr,
		const covergroup::iff								&iff_e,
		const std::function<void(covergroup::options_t &)>	&body) :
			obj(ObjType_Coverpoint), m_cp(0), m_iff(0), m_body_opts(body) {

	// Pop the sample expression
	ctor::inst()->pop_expr();
	m_target = expr.core();

	m_iff = iff_e.m_iff;
}

covergroup::coverpoint &covergroup::coverpoint::iff(const expr_base &expr) {
	ctor::inst()->pop_expr();
	m_iff = expr.core();
	return *this;
}

void covergroup::coverpoint::add_bins(bins *b) {
	m_bins.push_back(b);
}

void covergroup::coverpoint::add_ignore_bins(ignore_bins *b) {
	m_ignore_bins.push_back(b);
}

void covergroup::coverpoint::add_illegal_bins(illegal_bins *b) {
	m_illegal_bins.push_back(b);
}

double covergroup::coverpoint::get_coverage() {
	return m_cp->coverage();
}

void covergroup::coverpoint::build() {
	DEBUG_ENTER("coverpoint::build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
	ctor::inst()->push_build_scope(this);

	// TODO: initialize with options from above

	if (ctor::inst()->build_phase() == 0) {


		// We know enough to build the coverpoint itself
		m_cp = new ModelCoverpoint(
				m_target,
				name(),
				m_iff
				);

		// Propagate options from the parent
		covergroup *cg = static_cast<covergroup *>(parent());

		m_cp->options().propagate(cg->m_cg->options());

		if (m_body) {
			m_body();
		} else if (m_body_opts) {
			options_t options;

			// Propagate initial options from above
			options.at_least = m_cp->options().at_least();
			options.auto_bin_max = m_cp->options().auto_bin_max();

			m_body_opts(options);

			// Sync model options with user-specified values
			m_cp->options().weight(options.weight);
			m_cp->options().goal(options.goal);
			m_cp->options().comment(options.comment);
			m_cp->options().at_least(options.at_least);
			m_cp->options().auto_bin_max(options.auto_bin_max);
		}

		// We now have a collection of bins. Build the coverpoint model

		// Value ranges to be excluded based on ignore_bins, illegal_bins, etc
		ModelValRangelist exclude_bins;

		// TODO: build up exclusion list
		for (auto it=m_ignore_bins.begin(); it!=m_ignore_bins.end(); it++) {

		}

		// TODO: build up exclusion list
		for (auto it=m_illegal_bins.begin(); it!=m_illegal_bins.end(); it++) {

		}

		if (m_bins.size() > 0) {
			DEBUG("Coverpoint %s has user-defined bins", name().c_str());

		} else {
			DEBUG("Coverpoint %s has no user-defined bins ; autobinning", name().c_str());

		}
	}
	ctor::inst()->pop_build_scope();
	DEBUG_LEAVE("coverpoint::build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
}

covergroup::cross::cross(
		const scope					&name,
		const std::vector<cp_ref>	&terms) : obj(ObjType_CoverCross) {
	for (auto it=terms.begin(); it!=terms.end(); it++) {
		m_terms.push_back(it->m_cp);
	}
}

void covergroup::cross::build() {
	DEBUG_ENTER("cross::build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
	if (ctor::inst()->build_phase() == 2) {
		// Variables were built in phase 0, coverpoints in phase1
		// Now, we can grab appropriate references in phase 2
	}
	DEBUG_LEAVE("cross::build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
}

covergroup::bins::bins(
		const std::string	&name,
		const std::vector<expr_range>	&ranges) : m_name(name) {
	DEBUG_ENTER("bins::bins scope=%p", ctor::inst()->scope());
	covergroup::coverpoint *cp =
			ctor::inst()->build_scopeT<covergroup::coverpoint>();

	m_is_array = false;
	m_n_bins = 1;

	cp->add_bins(this);

	for (auto it=ranges.begin(); it!=ranges.end(); it++) {
		ctor::inst()->pop_expr();
		IModelExpr *lower_e = it->lower.core();
		if (it->upper.core()) {
			// We have two elements here
			ctor::inst()->pop_expr();
			IModelExpr *upper_e = it->upper.core();
			m_ranges.push_back(ModelValRange(
					ModelExprEvaluator().eval(lower_e),
					ModelExprEvaluator().eval(upper_e)));
			delete upper_e;
		} else {
			m_ranges.push_back(ModelValRange(
					ModelExprEvaluator().eval(lower_e)));
		}
		delete lower_e;
	}
	DEBUG_LEAVE("bins::bins");
}

covergroup::bins::bins(
		const std::string				&name,
		const expr_base					&sz,
		const std::vector<expr_range>	&ranges) : m_name(name) {
	ctor::inst()->build_scopeT<covergroup::coverpoint>()->add_bins(this);

	m_is_array = true;
	if (sz.core()) {
		ctor::inst()->pop_expr();
		ModelExpr *sz_e = sz.core();
		ModelVal sz_v = ModelExprEvaluator().eval(sz_e);
		delete sz_e;

		m_n_bins = sz_v.val_u();
	} else {
		// Empty range
		m_n_bins = -1;
	}

	for (auto it=ranges.begin(); it!=ranges.end(); it++) {
		ctor::inst()->pop_expr();
		fprintf(stdout, "pop range\n");
		if (it->upper.core()) {
			// We have two elements here
			ctor::inst()->pop_expr();
			fprintf(stdout, "pop range (2)\n");
		}
	}
}

covergroup::ignore_bins::ignore_bins(
		const std::string				&name,
		const std::vector<expr_range>	&ranges) : m_name(name) {
	ctor::inst()->build_scopeT<covergroup::coverpoint>()->add_ignore_bins(this);

}

covergroup::illegal_bins::illegal_bins(
		const std::string				&name,
		const std::vector<expr_range>	&ranges) : m_name(name) {
	ctor::inst()->build_scopeT<covergroup::coverpoint>()->add_illegal_bins(this);

}

void covergroup::add_coverpoint(coverpoint *cp) {
	m_coverpoints.push_back(cp);
}

void covergroup::add_cross(cross *cr) {
	m_crosses.push_back(cr);
}


} /* namespace facade */
} /* namespace vsc */

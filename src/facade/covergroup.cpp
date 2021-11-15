/*
 * covergroup.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#include "covergroup.h"
#include "ctor.h"
#include "Debug.h"

#define EN_DEBUG_COVERGROUP

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
		const std::function<void()>	&body) : obj(ObjType_Coverpoint) {
	// Pop the sample expression
	ctor::inst()->pop_expr();
}

covergroup::coverpoint::coverpoint(
		const scope											&name,
		const expr_base										&expr,
		const std::function<void(covergroup::options_t &)>	&body) :
			obj(ObjType_Coverpoint) {
	// Pop the sample expression
	ctor::inst()->pop_expr();
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

void covergroup::coverpoint::build() {
	DEBUG_ENTER("coverpoint::build %s (%d)",
			name().c_str(), ctor::inst()->build_phase());
	if (ctor::inst()->build_phase() == 0) {
		if (m_body) {
			m_body();
		} else {
			// TODO:
//			m_body_opts();
		}

		// We now have a collection of bins. Build the coverpoint model
	}
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
		const scope			&s) {

}

covergroup::bins::bins(
		const scope			&s,
		const std::vector<expr_range>	&ranges) {
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

covergroup::bins::bins(
		const scope						&s,
		const expr_base					&sz,
		const std::vector<expr_range>	&ranges) {
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
		const scope			&s,
		const std::vector<expr_range>	&ranges) {

}

covergroup::illegal_bins::illegal_bins(
		const scope			&s,
		const std::vector<expr_range>	&ranges) {

}

void covergroup::add_coverpoint(coverpoint *cp) {
	m_coverpoints.push_back(cp);
}

void covergroup::add_cross(cross *cr) {
	m_crosses.push_back(cr);
}


} /* namespace facade */
} /* namespace vsc */

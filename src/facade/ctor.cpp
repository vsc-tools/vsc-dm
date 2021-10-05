/*
 * ctor.cpp
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#include "ctor.h"

namespace vsc {
namespace facade {

ctor::ctor() {
	// TODO Auto-generated constructor stub

}

ctor::~ctor() {
	// TODO Auto-generated destructor stub
}

ctor *ctor::inst() {
	if (!m_inst) {
		m_inst = std::unique_ptr<ctor>(new ctor());
	}
	return m_inst.get();
}

void ctor::reset() {
	m_inst.release();
}

std::string ctor::scope_name() {
	return m_scope_s.back()->name();
}

ModelField * ctor::model_scope() {
	return 0;
}

rand_obj *ctor::scope() {
	if (m_scope_s.size() > 1) {
		return m_scope_s.at(m_scope_s.size()-2)->scope();
	} else {
		return 0;
	}
}

void ctor::scope_ctor(
			const std::string			&name,
			rand_obj					*scope,
			const std::type_info		*ti) {
	if (scope) {
		if (m_scope_s.size() > 0 && !m_scope_s.back()->scope()) {
			// This is the first scope entry. Update the
			// previous named entry
			m_scope_s.back()->scope(scope);
			m_scope_s.back()->ti(ti);
		} else if (m_scope_s.back()->scope() == scope) {
			fprintf(stdout, "  TODO: ignore inheritance for now\n");
		} else {
			fprintf(stdout, "  Error: unknown case\n");
		}
	} else {
		// Name entry
		m_scope_s.push_back(ctor_ctxt_up(new ctor_ctxt(name, 0, 0)));
	}
}

void ctor::scope_dtor(
			const std::string			&name,
			rand_obj					*scope,
			const std::type_info		*ti) {
	if (m_scope_s.back()->name() == name) {
		m_scope_s.pop_back();
	}
}

void ctor::push_expr_mode(bool expr_mode) {
	m_expr_mode.push_back(expr_mode);
}

bool ctor::is_expr_mode() const {
	return (m_expr_mode.size() && m_expr_mode.back());
}

void ctor::pop_expr_mode() {
	m_expr_mode.pop_back();
}

void ctor::push_expr(ModelExpr *e) {
	m_expr_s.push_back(ModelExprUP(e));
}

ModelExpr *ctor::expr() {
	return (m_expr_s.size())?m_expr_s.back().get():0;
}

ModelExpr *ctor::pop_expr() {
	ModelExpr *ret = m_expr_s.back().release();

	m_expr_s.pop_back();

	return ret;
}

std::unique_ptr<ctor> ctor::m_inst;

} /* namespace facade */
} /* namespace vsc */

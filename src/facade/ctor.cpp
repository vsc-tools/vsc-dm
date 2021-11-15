/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ctor.cpp
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#include "ctor.h"
#include "Debug.h"
#include "ModelConstraintExpr.h"

#define EN_DEBUG_CTOR

#ifdef EN_DEBUG_CTOR
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(ctor, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(ctor, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(ctor, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {
namespace facade {

ctor::ctor() : m_randstate(0) {
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
	std::string ret;
	if (m_scope_s.size()) {
		for (int32_t i=m_scope_s.size()-1; i>=0; i--) {
			if (m_scope_s.at(i)->name() != "") {
				ret = m_scope_s.at(i)->name();
				break;
			}
		}
	}
	return ret;
}

ModelField * ctor::model_scope() {
	return 0;
}

obj *ctor::scope(obj *s) {
	obj *ret = 0;
	int32_t count = 0;
	if (m_scope_s.size()) {
		for (int32_t i=m_scope_s.size()-1; i>=0; i--) {
			if (m_scope_s.at(i)->is_scope() &&
					m_scope_s.at(i)->scope() != s) {
				ret = m_scope_s.at(i)->scope();
				break;
			}
		}
	}
	return ret;
}

void ctor::scope_ctor(
			const std::string			&name,
			obj							*scope,
			const std::type_info		*ti) {
	DEBUG_ENTER("scope_ctor name=%s scope=%p ti=%p",
			name.c_str(), scope, ti);
	if (scope) {
		if (m_scope_s.size() > 0 && !m_scope_s.back()->scope()) {
			// This is the first scope entry. Update the
			// previous named entry
			m_scope_s.back()->scope(scope);
			m_scope_s.back()->push_ti(ti);
			m_scope_s.back()->is_scope(true);
		} else if (m_scope_s.back()->scope() == scope) {
			m_scope_s.back()->push_ti(ti);
		} else {
			fprintf(stdout, "  Error: unknown case\n");
		}
	} else {
		// Name entry
		m_scope_s.push_back(ctor_ctxt_up(new ctor_ctxt(name, 0)));
	}
	DEBUG_LEAVE("scope_ctor name=%s scope=%p ti=%p",
			name.c_str(), scope, ti);
}

void ctor::scope_dtor(
			const std::string			&name,
			obj							*scope,
			const std::type_info		*ti) {
	DEBUG_ENTER("scope_dtor name=%s scope=%p ti=%p",
			name.c_str(), scope, ti);
	if (m_scope_s.back()->name() == name) {
		DEBUG("Build constraints, since scope names match");
		if (m_scope_s.back()->scope() && m_scope_s.size() == 1) {
			DEBUG("scope_s.size=%d", m_scope_s.size());
			for (uint32_t i=0; i<3; i++) {
				push_build_phase(i);
				m_scope_s.back()->scope()->build();
				pop_build_phase();
			}
		}
		m_scope_s.pop_back();
	}
	DEBUG_LEAVE("scope_dtor name=%s scope=%p ti=%p",
			name.c_str(), scope, ti);
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

void ctor::push_constraint_scope(ModelConstraintScope *c) {
	m_constraint_scope_s.push_back(c);
}

ModelConstraintScope *ctor::pop_constraint_scope() {
	ModelConstraintScope *ret = m_constraint_scope_s.back();
	m_constraint_scope_s.pop_back();
	for (auto it=m_expr_s.begin();
			it!=m_expr_s.end(); it++) {
		ret->add_constraint(new ModelConstraintExpr(it->release()));
	}
	m_expr_s.clear();
	return ret;
}

DataTypeInt *ctor::type_int(
			bool		is_signed,
			int32_t		width) {
	std::unordered_map<int32_t,DataTypeIntUP>::const_iterator it;

	if (is_signed) {
		if ((it=m_si_type_m.find(width)) != m_si_type_m.end()) {
			return it->second.get();
		} else {
			DataTypeInt *dt = new DataTypeInt(true, width);
			m_si_type_m.insert({width, DataTypeIntUP(dt)});
			return dt;
		}
	} else {
		if ((it=m_ui_type_m.find(width)) != m_ui_type_m.end()) {
			return it->second.get();
		} else {
			DataTypeInt *dt = new DataTypeInt(false, width);
			m_ui_type_m.insert({width, DataTypeIntUP(dt)});
			return dt;
		}
	}
}

void ctor::push_build_phase(uint32_t p) {
	m_build_phase_s.push_back(p);
}

void ctor::pop_build_phase() {
	m_build_phase_s.pop_back();
}

RandState *ctor::mk_randstate() {
	uint32_t seed = m_randstate.randint32(1, 0x7FFFFFFF);
	return new RandState(seed);
}

std::unique_ptr<ctor> ctor::m_inst;

} /* namespace facade */
} /* namespace vsc */

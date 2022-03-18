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
 * SolverBitwuzla.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#include "Debug.h"
#include "bitwuzla/bitwuzla.h"
#include "SolverBitwuzla.h"
#include "SolverBitwuzlaSolveModelBuilder.h"

#define EN_DEBUG_SOLVER_BITWUZLA

#ifdef EN_DEBUG_SOLVER_BITWUZLA
DEBUG_SCOPE(SolverBitwuzla);
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(SolverBitwuzla, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(SolverBitwuzla, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(SolverBitwuzla, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

SolverBitwuzla::SolverBitwuzla() {
	m_bitwuzla = bitwuzla_new();
	/*
	bitwuzla_set_option(m_bitwuzla, BITWUZLA_OPT_LOGLEVEL, 3);
	bitwuzla_set_option(m_bitwuzla, BITWUZLA_OPT_VERBOSITY, 3);
	 */
	bitwuzla_set_option(m_bitwuzla, BITWUZLA_OPT_INCREMENTAL, 1);
	bitwuzla_set_option(m_bitwuzla, BITWUZLA_OPT_PRODUCE_MODELS, 1);
	m_issat = false;
	m_issat_valid = false;

}

SolverBitwuzla::~SolverBitwuzla() {
	// TODO Auto-generated destructor stub
	bitwuzla_delete(m_bitwuzla);
}

void SolverBitwuzla::initField(IModelField *f) {
	std::unordered_map<IModelField *, const BitwuzlaTerm *>::const_iterator it;

	if ((it=m_field_node_m.find(f)) == m_field_node_m.end()) {
		const BitwuzlaTerm *node = SolverBitwuzlaSolveModelBuilder(this).build(f);
		m_field_node_m.insert({f, node});
		m_issat_valid = false;
	}
}

	// Creates solver data for a constraint
void SolverBitwuzla::initConstraint(IModelConstraint *c) {
	std::unordered_map<IModelConstraint *, const BitwuzlaTerm *>::const_iterator it;

	if ((it=m_constraint_node_m.find(c)) == m_constraint_node_m.end()) {
		const BitwuzlaTerm *node = SolverBitwuzlaSolveModelBuilder(this).build(c);
		m_constraint_node_m.insert({c, node});
		m_issat_valid = false;
	}
}

void SolverBitwuzla::addAssume(IModelConstraint *c) {
	std::unordered_map<IModelConstraint *, const BitwuzlaTerm *>::const_iterator it;

	it = m_constraint_node_m.find(c);
	// TODO: assert ) == m_field_node_m.end()) {

	m_issat_valid = false;
	bitwuzla_assume(m_bitwuzla, it->second);
}

void SolverBitwuzla::addAssert(IModelConstraint *c) {
	std::unordered_map<IModelConstraint *, const BitwuzlaTerm *>::const_iterator it;

	it = m_constraint_node_m.find(c);

	// TODO: assert

	m_issat_valid = false;
	bitwuzla_assert(m_bitwuzla, it->second);
}

bool SolverBitwuzla::isSAT() {

	if (!m_issat_valid || !m_issat) {
		m_issat = (bitwuzla_check_sat(m_bitwuzla) == BITWUZLA_SAT);
		m_issat_valid = true;
	}

	return m_issat;
}

void SolverBitwuzla::setFieldValue(IModelField *f) {
	DEBUG_ENTER("setFieldValue %s", f->name().c_str());
	std::unordered_map<IModelField *, const BitwuzlaTerm *>::const_iterator it;

	if ((it=m_field_node_m.find(f)) == m_field_node_m.end()) {
		return;
	}

	// TODO: assert

	const BitwuzlaTerm *val = bitwuzla_get_value(m_bitwuzla, it->second);
	const char *bits = bitwuzla_get_bv_value(m_bitwuzla, val);
	DEBUG("bits=%s", bits);

	// Need to go
	// - size-32*1..size-32*0-1
	// - size-2*32..size-32*1-1
	const uint32_t elem_w = 32;
	int32_t size = bitwuzla_term_bv_get_size(it->second);
	int32_t it_idx = 0;
	int32_t bidx_lim = size;

	f->val()->from_bits(bits, size);

	DEBUG_LEAVE("setFieldValue %s", f->name().c_str());
}

const BitwuzlaSort *SolverBitwuzla::get_sort(int32_t width) {
	std::unordered_map<uint32_t, const BitwuzlaSort *>::const_iterator it;

	if ((it=m_sort_m.find(width)) != m_sort_m.end()) {
		return it->second;
	} else {
		const BitwuzlaSort *sort = bitwuzla_mk_bv_sort(m_bitwuzla, width);
		m_sort_m.insert({width, sort});
		return sort;
	}
}

void SolverBitwuzla::addFieldData(IModelField *f, const BitwuzlaTerm *n) {
	m_field_node_m.insert({f, n});
}

const BitwuzlaTerm *SolverBitwuzla::findFieldData(IModelField *f) {
	std::unordered_map<IModelField *, const BitwuzlaTerm *>::const_iterator it;

	if ((it=m_field_node_m.find(f)) != m_field_node_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}


} /* namespace vsc */

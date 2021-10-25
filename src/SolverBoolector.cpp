
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * SolverInstBoolector.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "boolector/boolector.h"
#include "Debug.h"
#include "SolverBoolector.h"
#include "SolverBoolectorSolveModelBuilder.h"

#undef EN_DEBUG_SOLVER_BITWUZLA

#ifdef EN_DEBUG_SOLVER_BITWUZLA
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(SolverBitwuzla, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(SolverBitwuzla, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(SolverBitwuzla, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

SolverBoolector::SolverBoolector() {
	m_btor = boolector_new();
	boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);
	boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);

	m_issat = false;
	m_issat_valid = false;

#ifdef UNDEFINED
	m_op = Op_CreateField; // throwaway
	m_node = 0;
	m_is_signed = false;
#endif
}

SolverBoolector::~SolverBoolector() {
	boolector_release_all(m_btor);
	boolector_delete(m_btor);

#ifdef UNDEFINED
	/*
	for (std::map<uint32_t,BoolectorSort>::iterator it=m_sort_m.begin();
			it!=m_sort_m.end(); it++) {
		boolector_release)
	}
	 */
#endif
}

	// Creates solver data for a field
void SolverBoolector::initField(ModelField *f) {
	std::unordered_map<ModelField *, BoolectorNode *>::const_iterator it;

	if ((it=m_field_node_m.find(f)) == m_field_node_m.end()) {
		BoolectorNode *node = SolverBoolectorSolveModelBuilder(this).build(f);
		m_field_node_m.insert({f, node});
		m_issat_valid = false;
	}
}

	// Creates solver data for a constraint
void SolverBoolector::initConstraint(ModelConstraint *c) {
	std::unordered_map<ModelConstraint *, BoolectorNode *>::const_iterator it;

	if ((it=m_constraint_node_m.find(c)) == m_constraint_node_m.end()) {
		BoolectorNode *node = SolverBoolectorSolveModelBuilder(this).build(c);
		m_constraint_node_m.insert({c, node});
		m_issat_valid = false;
	}
}

void SolverBoolector::addAssume(ModelConstraint *c) {
	std::unordered_map<ModelConstraint *, BoolectorNode *>::const_iterator it;

	it = m_constraint_node_m.find(c);
	// TODO: assert ) == m_field_node_m.end()) {

	m_issat_valid = false;
	boolector_assume(m_btor, it->second);
}

void SolverBoolector::addAssert(ModelConstraint *c) {
	std::unordered_map<ModelConstraint *, BoolectorNode *>::const_iterator it;

	it = m_constraint_node_m.find(c);

	// TODO: assert

	m_issat_valid = false;
	boolector_assert(m_btor, it->second);
}

bool SolverBoolector::isSAT() {

	if (!m_issat_valid) {
		m_issat = (boolector_sat(m_btor) == BTOR_RESULT_SAT);
		m_issat_valid = true;
	}

	return m_issat;
}

void SolverBoolector::setFieldValue(ModelField *f) {
	DEBUG_ENTER("setFieldValue %s", f->name().c_str());
	std::unordered_map<ModelField *, BoolectorNode *>::const_iterator it;

	it = m_field_node_m.find(f);

	// TODO: assert

	const char *bits = boolector_bv_assignment(m_btor, it->second);
	ModelVal::iterator val_it = f->val().begin();
	DEBUG("bits=%s", bits);

	// Need to go
	// - size-32*1..size-32*0-1
	// - size-2*32..size-32*1-1
	const uint32_t elem_w = 32;
	int32_t size = boolector_get_width(m_btor, it->second);
	int32_t it_idx = 0;
	int32_t bidx_lim = size;

	do {
		uint32_t tval = 0;
		int32_t bidx, bidx_lim_n;

		if (size > elem_w*(it_idx+1)) {
			bidx = size-(elem_w*(it_idx+1));
		} else {
			bidx = 0;
		}

		bidx_lim_n = bidx;
		while (bidx < bidx_lim) {
			tval <<= 1;
			tval |= (bits[bidx] == '1')?1:0;
			bidx++;
		}
		bidx_lim = bidx_lim_n;

		val_it.append(tval);

		it_idx++;
	} while (elem_w*it_idx < size);

	boolector_free_bv_assignment(m_btor, bits);
	DEBUG_LEAVE("setFieldValue %s", f->name().c_str());
}

BoolectorSort SolverBoolector::get_sort(int32_t width) {
	std::unordered_map<uint32_t, BoolectorSort>::const_iterator it;

	if ((it=m_sort_m.find(width)) != m_sort_m.end()) {
		return it->second;
	} else {
		BoolectorSort sort = boolector_bitvec_sort(m_btor, width);
		m_sort_m.insert({width, sort});
		return sort;
	}
}

void SolverBoolector::addFieldData(ModelField *f, BoolectorNode *n) {
	m_field_node_m.insert({f, n});
}

BoolectorNode *SolverBoolector::findFieldData(ModelField *f) {
	std::unordered_map<ModelField *, BoolectorNode *>::const_iterator it;

	if ((it=m_field_node_m.find(f)) != m_field_node_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}

} /* namespace vsc */

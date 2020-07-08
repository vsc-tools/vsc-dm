
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
 * VariableBoundVisitor.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#include "FieldBoundVisitor.h"

namespace vsc {

FieldBoundVisitor::FieldBoundVisitor() : m_depth(0), m_phase(0) {
	// TODO Auto-generated constructor stub

}

FieldBoundVisitor::~FieldBoundVisitor() {
	// TODO Auto-generated destructor stub
}

FieldBoundMap *FieldBoundVisitor::process(
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintBlockSP>	&constraints) {
	m_depth = 0;
	m_phase = 0;
	m_bounds = FieldBoundMapUP(new FieldBoundMap());

	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}

	m_phase = 1;
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}
	for (std::vector<ConstraintBlockSP>::const_iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		(*it)->accept(this);
	}

	// Finally, update derived calculations
	for (std::map<Field*,FieldBoundInfoUP>::iterator it=m_bounds->begin();
			it!=m_bounds->end(); it++) {
		it->second->update();
	}

	return m_bounds.release();
}

void FieldBoundVisitor::visitConstraintIf(ConstraintIf *c) {
	if (m_phase == 1) {
		m_depth++;
		VisitorBase::visitConstraintIf(c);
		m_depth--;
	}
}

// TODO: Implies

// TODO: Foreach (skip)

// TODO: Unique (skip)

void FieldBoundVisitor::visitExprBin(ExprBin *e) {
	// Simplest relationships are direct with respect to a variable:
	// <var> <op> <rhs>
	// <lhs> <op> <var>

}

// TODO: ExprIn

void FieldBoundVisitor::visitExprFieldRef(ExprFieldRef *e) {
	if (m_phase == 1) {
		// Ensure we mark this field as being consrained
		if (m_bounds->find(e->field()) != m_bounds->end()) {
			m_bounds->find(e->field())->second->is_constrained(true);
		}
	}

}

void FieldBoundVisitor::visitExprListSubscript(ExprListSubscript *e) {

}

void FieldBoundVisitor::visitFieldScalar(FieldScalar *f) {
	if (m_phase == 0) {
		FieldBoundInfo *info = new FieldBoundInfo(f->is_signed());

		if (f->is_signed()) {
			if (f->width() == 64) {
				// Special case
				info->domain().push_back({
					ExprValNumericSP(new ExprValNumeric(
							int64_t(0xFFFFFFFFFFFFFFFFULL),
							f->width(),
							false)),
					ExprValNumericSP(new ExprValNumeric(
							int64_t(0x7FFFFFFFFFFFFFFFULL),
							f->width(),
							false))
				});
			} else {
				info->domain().push_back({
					ExprValNumericSP(new ExprValNumeric(
							-(1ULL << f->width())-1,
							f->width(),
							false)),
					ExprValNumericSP(new ExprValNumeric(
							(1ULL << (f->width()-1))-1,
							f->width(),
							false))
				});
			}
		} else {
			if (f->width() == 64) {
				// Special case
				info->domain().push_back({
					ExprValNumeric::ZERO,
					ExprValNumericSP(new ExprValNumeric(
							0xFFFFFFFFFFFFFFFFULL,
							f->width(),
							false))
				});
			} else {
				info->domain().push_back({
					ExprValNumeric::ZERO,
					ExprValNumericSP(new ExprValNumeric(
							(1ULL << f->width())-1,
							f->width(),
							false))
				});
			}
		}

		m_bounds->insert({f, FieldBoundInfoUP(info)});
	}
}

// TODO: FieldEnum


} /* namespace vsc */

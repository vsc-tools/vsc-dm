
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
#include "expr/ExprBin.h"
#include "expr/ExprValNumeric.h"
#include "solver/FieldBoundMaxPropagator.h"
#include "solver/FieldBoundMinPropagator.h"
#include "solver/IsNonRandVisitor.h"

namespace vsc {

FieldBoundVisitor::FieldBoundVisitor() : m_depth(0), m_phase(0) {
	// TODO Auto-generated constructor stub

}

FieldBoundVisitor::~FieldBoundVisitor() {
	// TODO Auto-generated destructor stub
}

FieldBoundMap *FieldBoundVisitor::process(
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintStmtSP>		&constraints) {
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
	for (std::vector<ConstraintStmtSP>::const_iterator it=constraints.begin();
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

FieldBoundMap *FieldBoundVisitor::process(
			const std::set<Field *>					&fields,
			const std::vector<ConstraintStmt *>		&constraints,
			const std::vector<ConstraintSoft *>		&soft_constraints) {
	m_depth = 0;
	m_phase = 0;
	m_bounds = FieldBoundMapUP(new FieldBoundMap());

	for (std::set<Field *>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}

	m_phase = 1;
	for (std::set<Field *>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}
	for (std::vector<ConstraintStmt *>::const_iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		(*it)->accept(this);
	}

	for (std::vector<ConstraintSoft *>::const_iterator it=soft_constraints.begin();
			it!=soft_constraints.end(); it++) {
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

	if (m_phase != 1 || m_depth > 0) {
		// Ignore processing if we're either still collecting fields
		// or deeper in the expression tree
		return;
	}
	ExprFieldRef *lhs_ref = dynamic_cast<ExprFieldRef *>(e->lhs().get());
	ExprFieldRef *rhs_ref = dynamic_cast<ExprFieldRef *>(e->rhs().get());

	bool lhs_nonrand = IsNonRandVisitor().is_nonrand(e->lhs());
	bool rhs_nonrand = IsNonRandVisitor().is_nonrand(e->rhs());

	FieldBoundPropagator *propagator = 0;
	FieldBoundInfo *info = 0;
	if (lhs_ref && rhs_ref) {
		// rhs might be a fieldref too, and we'll check on that later
		Field *field = lhs_ref->field();
		info = m_bounds->find(field)->second.get();

		switch (e->op()) {
		case BinOp_Lt: {

		} break;
		case BinOp_Le: {

		} break;
		case BinOp_Gt: {

		} break;
		case BinOp_Ge: {

		} break;
		case BinOp_Eq: {

		} break;
		case BinOp_Ne: {

		} break;
		}
	} else if (lhs_ref && rhs_nonrand) {
		// LHS is a fieldref and the RHS is non-random
		info = m_bounds->find(lhs_ref->field())->second.get();
		switch (e->op()) {
		case BinOp_Lt: {
			propagator = new FieldBoundMaxPropagator(
					info,
					ExprSP(new ExprBin(
							e->rhs(),
							BinOp_Sub,
							ExprNumericLiteral::ONE)));
		} break;
		case BinOp_Le: {
			propagator = new FieldBoundMaxPropagator(
					info,
					e->rhs());
		} break;
		case BinOp_Gt: {
			propagator = new FieldBoundMinPropagator(
					info,
					ExprSP(new ExprBin(
							e->rhs(),
							BinOp_Add,
							ExprNumericLiteral::ONE)));
		} break;
		case BinOp_Ge: {
			propagator = new FieldBoundMinPropagator(
					info,
					e->rhs());
		} break;
		case BinOp_Eq: {

		} break;
		case BinOp_Ne: {

		} break;
		}

	} else if (rhs_ref && lhs_nonrand) {
		// RHS is a fieldref and the LHS is non-random

	}

	if (propagator && info) {
		info->add_propagator(propagator);
		propagator->propagate();
	}
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

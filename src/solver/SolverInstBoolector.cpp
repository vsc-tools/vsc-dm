/*
 * SolverInstBoolector.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "solver/SolverInstBoolector.h"
#include "solver/SolverDataBoolector.h"
#include "datamodel/FieldScalar.h"

namespace vsc {

SolverInstBoolector::SolverInstBoolector() {
	m_btor = boolector_new();
	boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);
	boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);
}

SolverInstBoolector::~SolverInstBoolector() {
	boolector_delete(m_btor);
}

	// Creates solver data for a field
void SolverInstBoolector::initField(Field *f) {
	m_op = Op_CreateField;
	f->accept(this);
}

	// Creates solver data for a constraint
void SolverInstBoolector::initConstraint(ConstraintStmt *c) {
	m_op = Op_CreateConstraint;
	fprintf(stdout, "initConstraint\n");
	c->accept(this);
}

void SolverInstBoolector::addAssume(ConstraintStmt *c) {
	boolector_assume(m_btor,
			static_cast<SolverDataBoolector *>(c->solver_data())->node());
}

void SolverInstBoolector::addAssert(ConstraintStmt *c) {
	boolector_assert(m_btor,
			static_cast<SolverDataBoolector *>(c->solver_data())->node());
}

bool SolverInstBoolector::failed(ConstraintStmt *c) {
	return boolector_failed(m_btor,
			static_cast<SolverDataBoolector *>(c->solver_data())->node());
}

bool SolverInstBoolector::isSAT() {
	int res = boolector_sat(m_btor);

	return (res == BTOR_RESULT_SAT);

}

void SolverInstBoolector::finalizeField(Field *f) {
	m_op = Op_FinalizeField;
	f->accept(this);
}

void SolverInstBoolector::visitExprBin(ExprBin *e) {
	switch (m_op) {
	case Op_CreateConstraint: {
		BoolectorNode *lhs_node, *rhs_node;
		bool lhs_is_signed, rhs_is_signed;
		uint32_t lhs_width, rhs_width;

		expr(e->lhs(), lhs_node, lhs_is_signed, lhs_width);
		expr(e->rhs(), rhs_node, rhs_is_signed, rhs_width);

		fprintf(stdout, "lhs=%p rhs=%p\n", lhs_node, rhs_node);
	} break;
	}
}

void SolverInstBoolector::visitExprNumericLiteral(ExprNumericLiteral *e) {
	switch (m_op) {
	case Op_CreateConstraint: {
		char tmp[65];
		for (uint32_t i=0; i<64; i++) {
			tmp[63-i] = (e->val() & (1 << i))?'1':'0';
		}
		tmp[64] = 0;
		m_node = boolector_const(m_btor, tmp);
		m_is_signed = false;
	} break;
	}
}

void SolverInstBoolector::visitFieldScalar(FieldScalar *f) {
	switch (m_op) {
	case Op_CreateField: {
		// Simple field
		BoolectorSort sort = get_sort(f->width());
		BoolectorNode *node = boolector_var(m_btor, sort, 0);
		f->solver_data(new SolverDataBoolector(node));
	} break;
	case Op_CreateConstraint: {
		// Field reference
		m_node = static_cast<SolverDataBoolector *>(f->solver_data())->node();
		m_is_signed = f->is_signed();
	} break;
	case Op_FinalizeField: {
		BoolectorNode *node = static_cast<SolverDataBoolector *>(f->solver_data())->node();
		const char *assign = boolector_bv_assignment(m_btor, node);

		uint64_t val = 0;
		for (uint32_t i=0; i<f->width(); i++) {
			val <<= 1;
			val |= (assign[i]== '1');
		}

		if (f->is_signed() && assign[0]) {
			// TODO: Sign bit is set, so sign-extend
		}

		f->val()->val(val);

		fprintf(stdout, "assignment=%s\n", assign);
		boolector_free_bv_assignment(m_btor, assign);
	} break;
	}
}

void SolverInstBoolector::expr(Expr *e, BoolectorNode *&node, bool &is_signed, uint32_t &width) {
	m_node = 0;
	m_is_signed = false;
	e->accept(this);
	node = m_node;
	is_signed = m_is_signed;
	if (node) {
		width = boolector_get_width(m_btor, node);
	}
}

BoolectorSort SolverInstBoolector::get_sort(int32_t width) {
	if (m_sort_m.find(width) == m_sort_m.end()) {
		BoolectorSort s = boolector_bitvec_sort(m_btor, width);
		m_sort_m.insert({width, s});
	}

	return m_sort_m.find(width)->second;
}

} /* namespace vsc */

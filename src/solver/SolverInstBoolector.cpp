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
	m_node = 0;

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

void SolverInstBoolector::visitFieldScalar(FieldScalar *f) {
	switch (m_op) {
	case Op_CreateField: {
		// Simple field
		BoolectorSort sort = get_sort(f->width());
		BoolectorNode *node = boolector_var(m_btor, sort, 0);
		f->solver_data(new SolverDataBoolector(node));
	} break;
	case Op_FinalizeField: {
		BoolectorNode *node = static_cast<SolverDataBoolector *>(f->solver_data())->node();
		const char *assign = boolector_bv_assignment(m_btor, node);

		// TODO: convert to field value

		fprintf(stdout, "assignment=%s\n", assign);
		boolector_free_bv_assignment(m_btor, assign);
	} break;
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

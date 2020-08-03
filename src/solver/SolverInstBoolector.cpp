
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

#include "solver/SolverInstBoolector.h"
#include "solver/SolverDataBoolector.h"
#include "datamodel/FieldScalar.h"

namespace vsc {

SolverInstBoolector::SolverInstBoolector() {
	m_btor = boolector_new();
	boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);
	boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);

	m_op = Op_CreateField; // throwaway
	m_node = 0;
	m_is_signed = false;
}

SolverInstBoolector::~SolverInstBoolector() {
	boolector_release_all(m_btor);
	boolector_delete(m_btor);

	/*
	for (std::map<uint32_t,BoolectorSort>::iterator it=m_sort_m.begin();
			it!=m_sort_m.end(); it++) {
		boolector_release)
	}
	 */
}

	// Creates solver data for a field
void SolverInstBoolector::initField(Field *f) {
	m_op = Op_CreateField;
	f->accept(this);
}

	// Creates solver data for a constraint
void SolverInstBoolector::initConstraint(ConstraintStmt *c) {
	m_op = Op_CreateConstraint;
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

void SolverInstBoolector::visitConstraintExpr(ConstraintExpr *c) {
	if (m_op == Op_CreateConstraint) {
		BoolectorNode *node;
		bool is_signed;
		uint32_t width;
		expr(c->expr(), node, is_signed, width);
		c->solver_data(new SolverDataBoolector(node));
	}
}

void SolverInstBoolector::visitConstraintScope(ConstraintScope *c) {
	if (m_op == Op_CreateConstraint) {
		VisitorBase::visitConstraintScope(c);

		if (c->constraints().size() == 0) {
			// TODO:
		} else if (c->constraints().size() == 1) {
			// Bring sub-node up
			c->solver_data(new SolverDataBoolector(m_node));
		} else {
			// AND together
			BoolectorNode *res_node = 0;
			for (std::vector<ConstraintStmtSP>::const_iterator it=c->constraints().begin();
					it!=c->constraints().end(); it++) {
				BoolectorNode *node = static_cast<SolverDataBoolector *>((*it)->solver_data())->node();

				if (res_node) {
					res_node = boolector_and(m_btor, res_node, node);
				} else {
					res_node = node;
				}
			}
			c->solver_data(new SolverDataBoolector(res_node));
		}
	}
}

void SolverInstBoolector::visitExprBin(ExprBin *e) {
	switch (m_op) {
	case Op_CreateConstraint: {
		BoolectorNode *lhs_node, *rhs_node;
		bool lhs_is_signed, rhs_is_signed;
		uint32_t lhs_width, rhs_width;

		expr(e->lhs().get(), lhs_node, lhs_is_signed, lhs_width);
		expr(e->rhs().get(), rhs_node, rhs_is_signed, rhs_width);

		resize(
				lhs_node, lhs_is_signed, lhs_width,
				rhs_node, rhs_is_signed, rhs_width);

		m_is_signed = (lhs_is_signed && rhs_is_signed);

		switch (e->op()) {
		case BinOp_Eq:
			m_node = boolector_eq(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Ne:
			m_node = boolector_ne(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Gt:
			if (m_is_signed) {
				m_node = boolector_sgt(m_btor, lhs_node, rhs_node);
			} else {
				m_node = boolector_ugt(m_btor, lhs_node, rhs_node);
			}
			break;
		case BinOp_Ge:
			if (m_is_signed) {
				m_node = boolector_sgte(m_btor, lhs_node, rhs_node);
			} else {
				m_node = boolector_ugte(m_btor, lhs_node, rhs_node);
			}
			break;
		case BinOp_Lt:
			if (m_is_signed) {
				m_node = boolector_slt(m_btor, lhs_node, rhs_node);
			} else {
				m_node = boolector_ult(m_btor, lhs_node, rhs_node);
			}
			break;
		case BinOp_Le:
			if (m_is_signed) {
				m_node = boolector_slte(m_btor, lhs_node, rhs_node);
			} else {
				m_node = boolector_ulte(m_btor, lhs_node, rhs_node);
			}
			break;
		case BinOp_Add:
			m_node = boolector_add(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Sub:
			m_node = boolector_sub(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Div:
			m_node = boolector_udiv(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Mul:
			m_node = boolector_mul(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Mod:
			m_node = boolector_urem(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_And:
			m_node = boolector_and(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Or:
			m_node = boolector_or(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Sll:
			m_node = boolector_sll(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Srl:
			m_node = boolector_srl(m_btor, lhs_node, rhs_node);
			break;
		case BinOp_Xor:
			m_node = boolector_xor(m_btor, lhs_node, rhs_node);
			break;
		default:
			fprintf(stdout, "unhandled binary op %d\n", e->op());
		}
	} break;
	}
}

void SolverInstBoolector::visitExprCond(ExprCond *e) {
	BoolectorNode *cond_node, *lhs_node, *rhs_node;
	bool cond_is_signed, lhs_is_signed, rhs_is_signed;
	uint32_t cond_width, lhs_width, rhs_width;

	expr(e->cond(), cond_node, cond_is_signed, cond_width);
	mk_bool(cond_node, cond_width);

	expr(e->true_e(), lhs_node, lhs_is_signed, lhs_width);
	expr(e->false_e(), rhs_node, rhs_is_signed, rhs_width);

	resize(
			lhs_node, lhs_is_signed, lhs_width,
			rhs_node, rhs_is_signed, rhs_width);

	m_node = boolector_cond(m_btor, cond_node, lhs_node, rhs_node);
	m_is_signed = (lhs_is_signed && rhs_is_signed);
}

void SolverInstBoolector::visitExprFieldRef(ExprFieldRef *e) {
	if (m_op == Op_CreateConstraint) {
		m_node = static_cast<SolverDataBoolector *>(e->field()->solver_data())->node();
		m_is_signed = false; // TODO:
	}

}

void SolverInstBoolector::visitExprValLiteral(ExprValLiteral *e) {
	switch (m_op) {
	case Op_CreateConstraint: {
		switch (e->val()->type()) {
		case ValType_Numeric: {
			char tmp[65];
			uint64_t val = static_cast<ExprValNumeric *>(e->val().get())->val_u();
			for (uint32_t i=0; i<64; i++) {
				tmp[63-i] = (val & (1ULL << i))?'1':'0';
			}
			tmp[64] = 0;
			m_node = boolector_const(m_btor, tmp);
			m_is_signed = false;
		} break;
		}
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


		// TODO: check if value is referenced before re-creating

		f->val(ExprValNumericSP(new ExprValNumeric(
				val,
				f->width(),
				f->is_signed())));

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

void SolverInstBoolector::mk_bool(BoolectorNode *&node, uint32_t &width) {
	if (width != 1) {
		node = boolector_ne(m_btor, node,
				boolector_zero(m_btor, get_sort(width)));
	}
}

void SolverInstBoolector::resize(
			BoolectorNode		*&n1,
			bool				n1_is_signed,
			uint32_t			n1_width,
			BoolectorNode		*&n2,
			bool				n2_is_signed,
			uint32_t			n2_width) {
	if (n1_width != n2_width) {
		if (n1_width > n2_width) {
			if (n1_is_signed && n2_is_signed) {
				n2 = boolector_sext(m_btor, n2, (n1_width-n2_width));
			} else {
				n2 = boolector_uext(m_btor, n2, (n1_width-n2_width));
			}
		} else {
			if (n1_is_signed && n2_is_signed) {
				n1 = boolector_sext(m_btor, n1, (n2_width-n1_width));
			} else {
				n1 = boolector_uext(m_btor, n1, (n2_width-n1_width));
			}
		}
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

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
 * SolverBoolectorModelBuilder.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "Debug.h"
#include "SolverBoolectorSolveModelBuilder.h"
#include "boolector/boolector.h"

#undef EN_DEBUG_SOLVER_BOOLECTOR_SOLVE_MODEL_BUILDER

#ifdef EN_DEBUG_SOLVER_BOOLECTOR_SOLVE_MODEL_BUILDER
DEBUG_SCOPE(SolverBoolectorSolveModelBuilder)
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(SolverBoolectorSolveModelBuilder, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(SolverBoolectorSolveModelBuilder, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(SolverBoolectorSolveModelBuilder, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

SolverBoolectorSolveModelBuilder::SolverBoolectorSolveModelBuilder(
		SolverBoolector *solver) : m_solver(solver) {
	// TODO Auto-generated constructor stub

}

SolverBoolectorSolveModelBuilder::~SolverBoolectorSolveModelBuilder() {
	// TODO Auto-generated destructor stub
}

BoolectorNode *SolverBoolectorSolveModelBuilder::build(ModelField *f) {
	m_width_s.clear();
	m_width_s.push_back(-1);

	f->accept(this);

	return m_node_i.second;
}

BoolectorNode *SolverBoolectorSolveModelBuilder::build(ModelConstraint *c) {
	m_width_s.clear();
	m_width_s.push_back(-1);

	m_node_i = {false, 0};

	c->accept(this);

	if (!m_node_i.second) {
		// Create a '1' node
		return boolector_one(
				m_solver->btor(),
				m_solver->get_sort(1));
	} else {
		return m_node_i.second;
	}
}

void SolverBoolectorSolveModelBuilder::visitDataTypeInt(DataTypeInt *t) {
	DEBUG_ENTER("visitDataTypeInt width=%d", t->width());
	BoolectorNode *n = boolector_var(m_solver->btor(),
			m_solver->get_sort(t->width()), 0);
	m_node_i = {t->is_signed(), n};
	DEBUG_LEAVE("visitDataTypeInt");
}

void SolverBoolectorSolveModelBuilder::visitDataTypeStruct(DataTypeStruct *t) {

}

void SolverBoolectorSolveModelBuilder::visitModelConstraint(ModelConstraint *c) {

}

void SolverBoolectorSolveModelBuilder::visitModelConstraintExpr(ModelConstraintExpr *c) {
	DEBUG_ENTER("visitModelConstraintExpr");
	m_node_i = {false, 0};

	m_width_s.push_back(1);
	c->expr()->accept(this);
	m_width_s.pop_back();

	if (!m_node_i.second) {
		fprintf(stdout, "Error: constraint not built\n");
	}

	// Ensure we have a boolean result
	m_node_i.second = toBoolNode(m_node_i.second);

	DEBUG_LEAVE("visitModelConstraintExpr");
}

void SolverBoolectorSolveModelBuilder::visitModelConstraintIf(ModelConstraintIf *c) {
	DEBUG_ENTER("visitModelConstrainIf");
	c->cond()->accept(this);
	BoolectorNode *cond_n = toBoolNode(m_node_i.second);

	c->true_c()->accept(this);
	BoolectorNode *true_n = toBoolNode(m_node_i.second);

	if (c->false_c()) {
		c->false_c()->accept(this);
		BoolectorNode *false_n = toBoolNode(m_node_i.second);

		m_node_i.second = boolector_cond(
				m_solver->btor(),
				cond_n,
				true_n,
				false_n);
		m_node_i.first = false;
	} else {
		// Simple 'implies'
		m_node_i.second = boolector_implies(
				m_solver->btor(),
				cond_n,
				true_n);
		m_node_i.first = false;
	}

	DEBUG_LEAVE("visitModelConstrainIf");
}

void SolverBoolectorSolveModelBuilder::visitModelConstraintImplies(
		ModelConstraintImplies *c) {
	DEBUG_ENTER("visitModelConstraintImplies");
	c->cond()->accept(this);
	BoolectorNode *cond_n = toBoolNode(m_node_i.second);

	c->body()->accept(this);
	BoolectorNode *body_n = toBoolNode(m_node_i.second);

	m_node_i.second = boolector_implies(
			m_solver->btor(),
			cond_n,
			body_n);
	m_node_i.first = false;
	DEBUG_LEAVE("visitModelConstraintImplies");
}

void SolverBoolectorSolveModelBuilder::visitModelConstraintScope(ModelConstraintScope *c) {
	DEBUG_ENTER("visitModelConstraintScope");
	BoolectorNode *result = 0;

	for (auto c_it=c->constraints().begin();
			c_it!=c->constraints().end(); c_it++) {
		m_node_i = {false, 0};
		(*c_it)->accept(this);

		if (m_node_i.second) {
			// Ensure the term is a boolean
			BoolectorNode *n = toBoolNode(m_node_i.second);

			if (result) {
				// Need to AND together
				result = boolector_and(m_solver->btor(),
						result,
						n);
			} else {
				result = n;
			}
		}
	}

	m_node_i = {false, result};
	DEBUG_LEAVE("visitModelConstraintScope");
}

void SolverBoolectorSolveModelBuilder::visitModelConstraintSoft(ModelConstraintSoft *c) {

}

void SolverBoolectorSolveModelBuilder::visitModelExprBin(ModelExprBin *e) {
	DEBUG_ENTER("visitModelExprBin %s", BinOp2Str_s(e->op()));
	int32_t ctx_width = m_width_s.back();

	if (e->lhs()->width() > ctx_width) {
		ctx_width = e->lhs()->width();
	}
	if (e->rhs()->width() > ctx_width) {
		ctx_width = e->rhs()->width();
	}

	node_info_t lhs_i = expr(e->lhs(), ctx_width);
	node_info_t rhs_i = expr(e->rhs(), ctx_width);

	bool is_signed = (lhs_i.first && rhs_i.first);

	BoolectorNode *lhs_n;
	BoolectorNode *rhs_n;

	if (e->op() == BinOp::LogAnd || e->op() == BinOp::LogOr) {
		lhs_n = toBoolNode(lhs_i.second);
		rhs_n = toBoolNode(rhs_i.second);
	} else {
		lhs_n =	extend(lhs_i.second, ctx_width, is_signed);
		rhs_n =	extend(rhs_i.second, ctx_width, is_signed);
	}

	BoolectorNode *result = 0;

	switch (e->op()) {
	case BinOp::Eq:
		result = boolector_eq(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Ne:
		result = boolector_ne(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Gt:
		if (is_signed) {
			result = boolector_sgt(m_solver->btor(), lhs_n, rhs_n);
		} else {
			result = boolector_ugt(m_solver->btor(), lhs_n, rhs_n);
		}
		break;
	case BinOp::Ge:
		if (is_signed) {
			result = boolector_sgte(m_solver->btor(), lhs_n, rhs_n);
		} else {
			result = boolector_ugte(m_solver->btor(), lhs_n, rhs_n);
		}
		break;
	case BinOp::Lt:
		if (is_signed) {
			result = boolector_slt(m_solver->btor(), lhs_n, rhs_n);
		} else {
			result = boolector_ult(m_solver->btor(), lhs_n, rhs_n);
		}
		break;
	case BinOp::Le:
		if (is_signed) {
			result = boolector_slte(m_solver->btor(), lhs_n, rhs_n);
		} else {
			result = boolector_ulte(m_solver->btor(), lhs_n, rhs_n);
		}
		break;
	case BinOp::Add:
		result = boolector_add(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Sub:
		result = boolector_sub(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Div:
		result = boolector_udiv(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Mul:
		result = boolector_mul(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Mod:
		if (is_signed) {
			result = boolector_srem(m_solver->btor(), lhs_n, rhs_n);
		} else {
			result = boolector_urem(m_solver->btor(), lhs_n, rhs_n);
		}
		break;
	case BinOp::BinAnd:
		result = boolector_and(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::BinOr:
		result = boolector_or(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Xor:
		result = boolector_xor(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::LogAnd:
		result = boolector_and(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::LogOr:
		result = boolector_or(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Sll:
		result = boolector_sll(m_solver->btor(), lhs_n, rhs_n);
		break;
	case BinOp::Srl:
		result = boolector_srl(m_solver->btor(), lhs_n, rhs_n);
		break;
	default:
		fprintf(stdout, "Error: unhandle bin op %d\n", e->op());
		break;

	}

	// If the context wants something larger, perform extension on the
	// backend vs the frontend. Not sure this is more efficient, but
	// shouldn't be worse
	if (e->op() == BinOp::LogAnd || e->op() == BinOp::LogOr) {
		if (ctx_width != 1) {
			result = extend(result, ctx_width, false);
		}
	}

	m_node_i = {is_signed, result};

	DEBUG_LEAVE("visitModelExprBin %s", BinOp2Str_s(e->op()));
}

void SolverBoolectorSolveModelBuilder::visitModelExprFieldRef(ModelExprFieldRef *e) {
	// Note: this should only be used for scalar fields
	BoolectorNode *n;
	bool is_signed = false;
	DEBUG_ENTER("visitModelExprFieldRef %s", e->field()->name().c_str());

	if (!(n=m_solver->findFieldData(e->field()))) {
		// Need to build this field
		DEBUG("Note: building field");
		e->field()->accept(this);
		n = m_node_i.second;
		is_signed = m_node_i.first;
		m_solver->addFieldData(e->field(), n);
	} else {
		// TODO: determine signedness of field
		DEBUG("n: %p", n);
	}

	m_node_i = {is_signed, n};
	DEBUG_LEAVE("visitModelExprFieldRef %s n=%p",
			e->field()->name().c_str(), m_node_i.second);
}

void SolverBoolectorSolveModelBuilder::visitModelExprPartSelect(
		ModelExprPartSelect *e) {
	int32_t ctx_width = m_width_s.back();
	DEBUG_ENTER("visitModelExprPartSelect");
	node_info_t lhs_i = expr(e->lhs(), ctx_width);

	m_node_i.first = false;
	m_node_i.second = boolector_slice(
			m_solver->btor(),
			lhs_i.second,
			e->upper(),
			e->lower());

	DEBUG_LEAVE("visitModelExprPartSelect");
}

void SolverBoolectorSolveModelBuilder::visitModelExprVal(ModelExprVal *e) {
	DEBUG_ENTER("visitModelExprVal");
	char *bits = (char *)alloca(e->val().bits()+1);
	e->val().to_bits(bits);

	DEBUG("bits=%s", bits);
	m_node_i.second = boolector_const(m_solver->btor(), bits);
	m_node_i.first = false; // TODO:

	DEBUG_LEAVE("visitModelExprVal");
}

void SolverBoolectorSolveModelBuilder::visitModelField(ModelField *f) {
	DEBUG_ENTER("visitModelField %s", f->name().c_str());
	if (f->is_flag_set(ModelFieldFlag_UsedRand)) {
		// Create a solver-variable representation for this
		m_field_s.push_back(f);
		if (f->datatype()) {
			f->datatype()->accept(this);
		} else {
			DEBUG("Note: no datatype");
		}
		m_field_s.pop_back();
	} else {
		// Create a value node
		char *bits = (char *)alloca(f->val().bits()+1);
		f->val().to_bits(bits);

		DEBUG("bits=%s", bits);
		m_node_i.second = boolector_const(m_solver->btor(), bits);
		m_node_i.first = false; // TODO:
	}
	DEBUG_LEAVE("visitModelField %s", f->name().c_str());
}

void SolverBoolectorSolveModelBuilder::visitModelFieldRoot(ModelFieldRoot *f) {
	DEBUG_ENTER("visitModelFieldRoot %s", f->name().c_str());
	VisitorBase::visitModelFieldRoot(f);
	DEBUG_LEAVE("visitModelFieldRoot %s", f->name().c_str());
}

void SolverBoolectorSolveModelBuilder::visitModelFieldType(ModelFieldType *f) {

}

BoolectorNode *SolverBoolectorSolveModelBuilder::toBoolNode(BoolectorNode *n) {
	uint32_t width;

	if ((width=boolector_get_width(m_solver->btor(), n)) != 1) {
		return boolector_ne(
				m_solver->btor(),
				n,
				boolector_zero(m_solver->btor(),
						m_solver->get_sort(width)));
	} else {
		return n;
	}
}

SolverBoolectorSolveModelBuilder::node_info_t SolverBoolectorSolveModelBuilder::expr(
		ModelExpr 		*e,
		int32_t 		ctx_width) {
	m_node_i = {false, 0};
	m_width_s.push_back(ctx_width);
	e->accept(this);
	m_width_s.pop_back();
	return m_node_i;
}

BoolectorNode *SolverBoolectorSolveModelBuilder::extend(
			BoolectorNode		*n,
			int32_t				ctx_width,
			bool				is_signed) {
	int32_t width = boolector_get_width(m_solver->btor(), n);
	DEBUG_ENTER("extend width=%d ctx_width=%d is_signed=%d",
			width, ctx_width, is_signed);

	if (ctx_width > width) {
		if (is_signed) {
			DEBUG("Sign-extend");
			n = boolector_sext(
					m_solver->btor(),
					n,
					(ctx_width-width));
		} else {
			DEBUG("Unsigned-extend");
			n = boolector_uext(
					m_solver->btor(),
					n,
					(ctx_width-width));
		}
	}
	DEBUG_LEAVE("extend width=%d ctx_width=%d is_signed=%d",
			width, ctx_width, is_signed);
	return n;
}

} /* namespace vsc */

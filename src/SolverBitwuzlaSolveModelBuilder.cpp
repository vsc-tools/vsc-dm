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
 * SolverBitwuzlaModelBuilder.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "Debug.h"
#include "SolverBitwuzlaSolveModelBuilder.h"
#include "bitwuzla/bitwuzla.h"
#include "vsc/impl/TaskIsDataTypeSigned.h"

#define EN_DEBUG_SOLVER_BITWUZLA_SOLVE_MODEL_BUILDER

#ifdef EN_DEBUG_SOLVER_BITWUZLA_SOLVE_MODEL_BUILDER
DEBUG_SCOPE(SolverBitwuzlaSolveModelBuilder);
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(SolverBitwuzlaSolveModelBuilder, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(SolverBitwuzlaSolveModelBuilder, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(SolverBitwuzlaSolveModelBuilder, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

SolverBitwuzlaSolveModelBuilder::SolverBitwuzlaSolveModelBuilder(
		SolverBitwuzla *solver) : m_solver(solver) {
	// TODO Auto-generated constructor stub

}

SolverBitwuzlaSolveModelBuilder::~SolverBitwuzlaSolveModelBuilder() {
	// TODO Auto-generated destructor stub
}

const BitwuzlaTerm *SolverBitwuzlaSolveModelBuilder::build(IModelField *f) {
	m_width_s.clear();
	m_width_s.push_back(-1);

	f->accept(this);

	return m_node_i.second;
}

const BitwuzlaTerm *SolverBitwuzlaSolveModelBuilder::build(IModelConstraint *c) {
	DEBUG_ENTER("build(ModelConstraint)");
	m_width_s.clear();
	m_width_s.push_back(-1);

	m_node_i = {false, 0};

	c->accept(this);

	if (!m_node_i.second) {
		// Create a '1' node
		DEBUG_LEAVE("build(ModelConstraint) (const-1)");
		return bitwuzla_mk_bv_one(
				m_solver->bitwuzla(),
				m_solver->get_sort(1));
	} else {
		DEBUG_LEAVE("build(ModelConstraint) (m_node_i.second=%p)", m_node_i.second);
		return m_node_i.second;
	}
}

void SolverBitwuzlaSolveModelBuilder::visitDataTypeEnum(IDataTypeEnum *t) {
	DEBUG_ENTER("visitDataTypeInt");
	int32_t width = t->getWidth(); // TODO: should calculate from definition
	const BitwuzlaTerm *n = bitwuzla_mk_const(m_solver->bitwuzla(),
			m_solver->get_sort(width), 0);
	m_node_i = {t->isSigned(), n};
	DEBUG_LEAVE("visitDataTypeInt");
}

void SolverBitwuzlaSolveModelBuilder::visitDataTypeInt(IDataTypeInt *t) {
	DEBUG_ENTER("visitDataTypeInt");
	const BitwuzlaTerm *n = bitwuzla_mk_const(m_solver->bitwuzla(),
			m_solver->get_sort(t->width()), 0);
	m_node_i = {t->is_signed(), n};
	DEBUG_LEAVE("visitDataTypeInt");
}

void SolverBitwuzlaSolveModelBuilder::visitDataTypeStruct(IDataTypeStruct *t) {

}

void SolverBitwuzlaSolveModelBuilder::visitModelConstraint(IModelConstraint *c) {

}

void SolverBitwuzlaSolveModelBuilder::visitModelConstraintExpr(IModelConstraintExpr *c) {
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

void SolverBitwuzlaSolveModelBuilder::visitModelConstraintScope(IModelConstraintScope *c) {
	DEBUG_ENTER("visitModelConstraintScope");
	const BitwuzlaTerm *result = 0;

	for (auto c_it=c->constraints().begin();
			c_it!=c->constraints().end(); c_it++) {
		m_node_i = {false, 0};
		(*c_it)->accept(this);

		if (m_node_i.second) {
			// Ensure the term is a boolean
			const BitwuzlaTerm *n = toBoolNode(m_node_i.second);

			if (result) {
				// Need to AND together
				result = bitwuzla_mk_term2(
						m_solver->bitwuzla(),
						BITWUZLA_KIND_BV_AND,
						result,
						n);
			} else {
				result = n;
			}
		} else {
			DEBUG("Note: no result");
		}
	}

	m_node_i = {false, result};
	DEBUG_LEAVE("visitModelConstraintScope");
}

void SolverBitwuzlaSolveModelBuilder::visitModelConstraintSoft(IModelConstraintSoft *c) {

}

void SolverBitwuzlaSolveModelBuilder::visitModelExprBin(IModelExprBin *e) {
	DEBUG_ENTER("visitModelExprBin");
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

	const BitwuzlaTerm *lhs_n;
	const BitwuzlaTerm *rhs_n;

	if (e->op() == BinOp::LogAnd || e->op() == BinOp::LogOr) {
		lhs_n = toBoolNode(lhs_i.second);
		rhs_n = toBoolNode(rhs_i.second);
	} else {
		lhs_n =	extend(lhs_i.second, ctx_width, is_signed);
		rhs_n =	extend(rhs_i.second, ctx_width, is_signed);
	}

	const BitwuzlaTerm *result = 0;

	switch (e->op()) {
	case BinOp::Eq:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_EQUAL,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Ne:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_DISTINCT,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Gt:
		if (is_signed) {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_SGT,
					lhs_n,
					rhs_n);
		} else {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_UGT,
					lhs_n,
					rhs_n);
		}
		break;
	case BinOp::Ge:
		if (is_signed) {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_SGE,
					lhs_n,
					rhs_n);
		} else {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_UGE,
					lhs_n,
					rhs_n);
		}
		break;
	case BinOp::Lt:
		if (is_signed) {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_SLT,
					lhs_n,
					rhs_n);
		} else {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_ULT,
					lhs_n,
					rhs_n);
		}
		break;
	case BinOp::Le:
		if (is_signed) {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_SLE,
					lhs_n,
					rhs_n);
		} else {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_ULE,
					lhs_n,
					rhs_n);
		}
		break;
	case BinOp::Add:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_ADD,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Sub:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_SUB,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Div:
		if (is_signed) {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_SDIV,
					lhs_n,
					rhs_n);
		} else {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_UDIV,
					lhs_n,
					rhs_n);
		}
		break;
	case BinOp::Mul:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_MUL,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Mod:
		if (is_signed) {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_SREM,
					lhs_n,
					rhs_n);
		} else {
			result = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_UREM,
					lhs_n,
					rhs_n);
		}
		break;
	case BinOp::BinAnd:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_AND,
				lhs_n,
				rhs_n);
		break;
	case BinOp::BinOr:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_OR,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Xor:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_XOR,
				lhs_n,
				rhs_n);
		break;
	case BinOp::LogAnd:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_AND,
				lhs_n,
				rhs_n);
		break;
	case BinOp::LogOr:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_OR,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Sll:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_SHL,
				lhs_n,
				rhs_n);
		break;
	case BinOp::Srl:
		result = bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_BV_SHR,
				lhs_n,
				rhs_n);
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

	DEBUG_LEAVE("visitModelExprBin");
}

void SolverBitwuzlaSolveModelBuilder::visitModelExprFieldRef(IModelExprFieldRef *e) {
	// Note: this should only be used for scalar fields
	const BitwuzlaTerm *n;
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

void SolverBitwuzlaSolveModelBuilder::visitModelExprIn(IModelExprIn *e) {
	DEBUG_ENTER("visitModelExprIn");
	int32_t ctx_width = m_width_s.back();
	node_info_t lhs_i = expr(e->lhs(), ctx_width);

	if (e->lhs()->width() > ctx_width) {
		ctx_width = e->lhs()->width();
	}

	if (e->rangelist()->width() > ctx_width) {
		ctx_width = e->rangelist()->width();
	}

	// TODO: need to consider sign of rangelist elements?
	bool is_signed = lhs_i.first;

	lhs_i.second = extend(lhs_i.second, ctx_width, is_signed);

	const BitwuzlaTerm *n = 0;

	for (auto r_it=e->rangelist()->ranges().begin();
			r_it!=e->rangelist()->ranges().end(); r_it++) {
		const BitwuzlaTerm *t;
		// Individual term
		if ((*r_it)->upper()) {
			// Dual-value
			node_info_t rvl_i = expr((*r_it)->lower(), ctx_width);
			node_info_t rvu_i = expr((*r_it)->upper(), ctx_width);
			rvl_i.second = extend(rvl_i.second, ctx_width, is_signed);
			rvu_i.second = extend(rvu_i.second, ctx_width, is_signed);
			if (is_signed) {
				t = bitwuzla_mk_term2(
						m_solver->bitwuzla(),
						BITWUZLA_KIND_BV_AND,
						bitwuzla_mk_term2(
								m_solver->bitwuzla(),
								BITWUZLA_KIND_BV_SGE,
								lhs_i.second,
								rvl_i.second),
						bitwuzla_mk_term2(
								m_solver->bitwuzla(),
								BITWUZLA_KIND_BV_SLE,
								lhs_i.second,
								rvu_i.second));
			} else {
				const BitwuzlaTerm *l1 = bitwuzla_mk_term2(
								m_solver->bitwuzla(),
								BITWUZLA_KIND_BV_UGE,
								lhs_i.second,
								rvl_i.second);
				const BitwuzlaTerm *l2 = bitwuzla_mk_term2(
								m_solver->bitwuzla(),
								BITWUZLA_KIND_BV_ULE,
								lhs_i.second,
								rvu_i.second);
				t =	bitwuzla_mk_term2(
						m_solver->bitwuzla(),
						BITWUZLA_KIND_BV_AND,
						l1,
						l2);
			}
		} else {
			// Single value
			node_info_t rv_i = expr((*r_it)->lower(), ctx_width);
			t = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_EQUAL,
					lhs_i.second,
					rv_i.second);
		}

		if (!n) {
			n = t;
		} else {
			n = bitwuzla_mk_term2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_OR,
					n,
					t);
		}
	}

	m_node_i.second = n;
	m_node_i.first = false;


	DEBUG_LEAVE("visitModelExprIn");
}

void SolverBitwuzlaSolveModelBuilder::visitModelExprPartSelect(
		IModelExprPartSelect *e) {
	int32_t ctx_width = m_width_s.back();
	DEBUG_ENTER("visitModelExprPartSelect");
	node_info_t lhs_i = expr(e->lhs(), ctx_width);

	m_node_i.first = false;
	m_node_i.second = bitwuzla_mk_term1_indexed2(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_EXTRACT,
					lhs_i.second,
					e->upper(),
					e->lower());

	DEBUG_LEAVE("visitModelExprPartSelect");
}

void SolverBitwuzlaSolveModelBuilder::visitModelExprVal(IModelExprVal *e) {
	DEBUG_ENTER("visitModelExprVal");

	if (e->val()->bits() <= 64) {
		m_node_i.second = bitwuzla_mk_bv_value_uint64(
				m_solver->bitwuzla(),
				m_solver->get_sort(e->val()->bits()),
				e->val()->val_u());
		m_node_i.first = false; // TODO:
	} else {
		char *bits = (char *)alloca(e->val()->bits()+1);
		e->val()->to_bits(bits);

		DEBUG("bits=%s", bits);
		m_node_i.second = bitwuzla_mk_bv_value(
				m_solver->bitwuzla(),
				m_solver->get_sort(e->val()->bits()),
				bits,
				BITWUZLA_BV_BASE_BIN);
		m_node_i.first = false; // TODO:
	}

	DEBUG_LEAVE("visitModelExprVal");
}

void SolverBitwuzlaSolveModelBuilder::visitModelField(IModelField *f) {
	DEBUG_ENTER("visitModelField %s", f->name().c_str());
	m_field_s.push_back(f);
	if (f->getDataType()) {
		f->getDataType()->accept(this);
	} else {
		DEBUG("Note: no datatype");
	}

	// TODO: must handle
	m_field_s.pop_back();
	DEBUG_LEAVE("visitModelField %s", f->name().c_str());
}

void SolverBitwuzlaSolveModelBuilder::visitModelFieldRoot(IModelFieldRoot *f) {
	DEBUG_ENTER("visitModelFieldRoot %s", f->name().c_str());
	VisitorBase::visitModelFieldRoot(f);
	DEBUG_LEAVE("visitModelFieldRoot %s", f->name().c_str());
}

void SolverBitwuzlaSolveModelBuilder::visitModelFieldType(IModelFieldType *f) {
	DEBUG_ENTER("visitModelFieldType");
	m_field_s.push_back(f);
	if (f->getDataType()) {
		f->getDataType()->accept(this);
	} else {
		DEBUG("Note: no datatype");
	}
	m_field_s.pop_back();
	DEBUG_LEAVE("visitModelFieldType");
}

const BitwuzlaTerm *SolverBitwuzlaSolveModelBuilder::toBoolNode(const BitwuzlaTerm *n) {
	uint32_t width;
	DEBUG_ENTER("toBoolNode (width=%d)", bitwuzla_term_bv_get_size(n));

	if ((width=bitwuzla_term_bv_get_size(n)) != 1) {
		DEBUG("Convert to bool");
		DEBUG_LEAVE("toBoolNode (width=%d)", bitwuzla_term_bv_get_size(n));
		return bitwuzla_mk_term2(
				m_solver->bitwuzla(),
				BITWUZLA_KIND_DISTINCT,
				n,
				bitwuzla_mk_bv_zero(
						m_solver->bitwuzla(),
						m_solver->get_sort(width)));
	} else {
		DEBUG_LEAVE("toBoolNode (width=%d)", bitwuzla_term_bv_get_size(n));
		return n;
	}
}

SolverBitwuzlaSolveModelBuilder::node_info_t SolverBitwuzlaSolveModelBuilder::expr(
		IModelExpr 		*e,
		int32_t 		ctx_width) {
	m_node_i = {false, 0};
	m_width_s.push_back(ctx_width);
	e->accept(this);
	m_width_s.pop_back();
	return m_node_i;
}

const BitwuzlaTerm *SolverBitwuzlaSolveModelBuilder::extend(
			const BitwuzlaTerm		*n,
			int32_t					ctx_width,
			bool					is_signed) {
	DEBUG_ENTER("extend width=%d ctx_width=%d",
			bitwuzla_term_bv_get_size(n), ctx_width);

	int32_t width = bitwuzla_term_bv_get_size(n);

	if (ctx_width > width) {
		if (is_signed) {
			DEBUG("Sign Extend");
			DEBUG_LEAVE("extend width=%d ctx_width=%d",
					bitwuzla_term_bv_get_size(n), ctx_width);
			return bitwuzla_mk_term1_indexed1(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_SIGN_EXTEND,
					n,
					(ctx_width-width));
		} else {
			DEBUG("Zero Extend");
			DEBUG_LEAVE("extend width=%d ctx_width=%d",
					bitwuzla_term_bv_get_size(n), ctx_width);
			return bitwuzla_mk_term1_indexed1(
					m_solver->bitwuzla(),
					BITWUZLA_KIND_BV_ZERO_EXTEND,
					n,
					(ctx_width-width));
		}
	} else {
		return n;
	}
	DEBUG_LEAVE("extend width=%d ctx_width=%d",
			bitwuzla_term_bv_get_size(n), ctx_width);
}

} /* namespace vsc */

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
 * ModelExprBin.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#include "ModelExprBin.h"
#include "ModelValOp.h"

namespace vsc {

ModelExprBin::ModelExprBin(
		ModelExpr			*lhs,
		BinOp				op,
		ModelExpr			*rhs) :
			m_lhs(lhs), m_op(op), m_rhs(rhs) {

	m_signed = false;

	switch (op) {
	case BinOp::Eq:
	case BinOp::Ge:
	case BinOp::Le:
	case BinOp::Gt:
	case BinOp::Lt:
	case BinOp::Ne:
		m_width = 1;
		break;
	default:
		m_width = (lhs->width() > rhs->width())?lhs->width():rhs->width();
		break;
	}
}

ModelExprBin::~ModelExprBin() {
	// TODO Auto-generated destructor stub
}

void ModelExprBin::eval(IModelVal *dst) {
	ModelVal lhs(m_width), rhs(m_width);
	m_lhs->eval(&lhs);
	m_rhs->eval(&rhs);

	if (m_width <= 64) {
		switch (m_op) {
		case BinOp::Add:
			dst->val_u(lhs.val_u() + rhs.val_u(), m_width);
			dst->bits(m_width);
			break;
		case BinOp::Eq:
			ModelValOp::eq(dst, &lhs, &rhs);
			break;
		case BinOp::Ne:
			ModelValOp::ne(dst, &lhs, &rhs);
			break;
		case BinOp::Ge:
			// Expression must be signed or unsigned
			if (m_signed) {
				ModelValOp::sge(dst, &lhs, &rhs);
			} else {
				ModelValOp::uge(dst, &lhs, &rhs);
			}
			break;
		case BinOp::Gt:
			// Expression must be signed or unsigned
			if (m_signed) {
				ModelValOp::sgt(dst, &lhs, &rhs);
			} else {
				ModelValOp::ugt(dst, &lhs, &rhs);
			}
			break;
		case BinOp::Le:
			// Expression must be signed or unsigned
			if (m_signed) {
				ModelValOp::sle(dst, &lhs, &rhs);
			} else {
				ModelValOp::ule(dst, &lhs, &rhs);
			}
			break;
		case BinOp::Lt:
			// Expression must be signed or unsigned
			if (m_signed) {
				ModelValOp::slt(dst, &lhs, &rhs);
			} else {
				ModelValOp::ult(dst, &lhs, &rhs);
			}
			break;
		case BinOp::LogAnd:
			ModelValOp::log_and(dst, &lhs, &rhs);
			dst->bits(m_width);
			break;
		case BinOp::LogOr:
			ModelValOp::log_or(dst, &lhs, &rhs);
			dst->bits(m_width);
			break;
		case BinOp::Sll:
			ModelValOp::sll(dst, &lhs, &rhs);
			dst->bits(m_width);
			break;
		case BinOp::Srl:
			if (m_signed) {
				ModelValOp::sra(dst, &lhs, &rhs);
			} else {
				ModelValOp::srl(dst, &lhs, &rhs);
			}
			dst->bits(m_width);
			break;
		case BinOp::Sub:
			if (m_signed) {
				dst->val_u(lhs.val_i() - rhs.val_i(), m_width);
				dst->bits(m_width);
			} else {
				dst->val_u(lhs.val_u() - rhs.val_u(), m_width);
				dst->bits(m_width);
			}
			break;
		case BinOp::Xor:
			dst->val_u(lhs.val_u() ^ rhs.val_u(), m_width);
			dst->bits(m_width);
			break;
		case BinOp::BinAnd:
			dst->val_u(lhs.val_u() != 0 && rhs.val_u() != 0);
			break;
		case BinOp::BinOr:
			dst->val_u(lhs.val_u() != 0 || rhs.val_u() != 0);
			break;
		}
	} else {
		// Slow path?

	}
}

void ModelExprBin::eq_op_64(
		IModelVal 		*dst,
		const ModelVal 	&op1,
		const ModelVal 	&op2) {
	dst->val_u(op1.val_u() == op2.val_u());
	dst->bits(1);
}

} /* namespace vsc */

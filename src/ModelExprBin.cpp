/*
 * ModelExprBin.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#include "ModelExprBin.h"

namespace vsc {

ModelExprBin::ModelExprBin(
		ModelExpr			*lhs,
		BinOp				op,
		ModelExpr			*rhs) :
			m_lhs(lhs), m_op(op), m_rhs(rhs) {

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

} /* namespace vsc */

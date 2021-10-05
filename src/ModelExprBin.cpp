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
	// TODO Auto-generated constructor stub

}

ModelExprBin::~ModelExprBin() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

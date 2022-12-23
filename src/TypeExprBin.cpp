/*
 * TypeExprBin.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#include "TypeExprBin.h"

namespace vsc {
namespace dm {

TypeExprBin::TypeExprBin(
		ITypeExpr			*lhs,
		BinOp				op,
		ITypeExpr			*rhs) : m_lhs(lhs), m_op(op), m_rhs(rhs) {

}

TypeExprBin::~TypeExprBin() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */


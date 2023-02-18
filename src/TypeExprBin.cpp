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
		ITypeExpr			*rhs,
        bool                lhs_owned,
        bool                rhs_owned) : 
        m_lhs(lhs, lhs_owned), m_op(op), 
        m_rhs(rhs, rhs_owned) {

}

TypeExprBin::~TypeExprBin() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */


/*
 * TypeConstraintExpr.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#include "TypeConstraintExpr.h"

namespace vsc {
namespace dm {

TypeConstraintExpr::TypeConstraintExpr(
    ITypeExpr       *expr,
    bool            owned) : m_expr(expr, owned) {
	// TODO Auto-generated constructor stub

}

TypeConstraintExpr::~TypeConstraintExpr() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */


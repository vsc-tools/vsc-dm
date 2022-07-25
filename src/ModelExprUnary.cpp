/*
 * ModelExprUnary.cpp
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#include "ModelExprUnary.h"

namespace vsc {

ModelExprUnary::ModelExprUnary(
		UnaryOp			op,
		IModelExpr		*expr) : m_expr(expr), m_op(op) {
	m_width = expr->width();

}

ModelExprUnary::~ModelExprUnary() {
	// TODO Auto-generated destructor stub
}

void ModelExprUnary::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprUnary::eval\n");
}

} /* namespace vsc */

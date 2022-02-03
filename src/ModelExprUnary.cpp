/*
 * ModelExprUnary.cpp
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#include "ModelExprUnary.h"

namespace vsc {

ModelExprUnary::ModelExprUnary(
		ModelExpr		*expr,
		UnaryOp			op) : m_expr(expr), m_op(op) {
	// TODO Auto-generated constructor stub

}

ModelExprUnary::~ModelExprUnary() {
	// TODO Auto-generated destructor stub
}

void ModelExprUnary::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprUnary::eval\n");
}

} /* namespace vsc */

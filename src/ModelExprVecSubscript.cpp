/*
 * ModelExprVecSubscript.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#include <stdio.h>
#include "ModelExprVecSubscript.h"

namespace vsc {
namespace dm {

ModelExprVecSubscript::ModelExprVecSubscript(
		IModelExpr			*expr,
		IModelExpr			*subscript)
				: m_expr(expr), m_subscript(subscript) {

}

ModelExprVecSubscript::~ModelExprVecSubscript() {
	// TODO Auto-generated destructor stub
}

void ModelExprVecSubscript::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprVecSubscript::eval\n");
}

}
} /* namespace vsc */


/*
 * ModelExprIn.cpp
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#include <stdio.h>
#include "ModelExprIn.h"

namespace vsc {

ModelExprIn::ModelExprIn(
		IModelExpr			*lhs,
		IModelExprRangelist	*rangelist) : m_lhs(lhs), m_rangelist(rangelist) {

}

ModelExprIn::~ModelExprIn() {
	// TODO Auto-generated destructor stub
}

void ModelExprIn::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprIn::eval\n");
}

} /* namespace vsc */

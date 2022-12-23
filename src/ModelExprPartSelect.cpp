/*
 * ModelExprPartSelect.cpp
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#include <stdio.h>
#include "ModelExprPartSelect.h"

namespace vsc {
namespace dm {

ModelExprPartSelect::ModelExprPartSelect(
		IModelExpr				*lhs,
		int32_t					upper,
		int32_t					lower) :
				m_lhs(lhs), m_upper(upper), m_lower(lower) {

}

ModelExprPartSelect::~ModelExprPartSelect() {
	// TODO Auto-generated destructor stub
}

void ModelExprPartSelect::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprPartSelect::eval\n");
}

}
} /* namespace vsc */

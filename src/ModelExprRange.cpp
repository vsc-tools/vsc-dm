/*
 * ModelExprRange.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#include <stdio.h>
#include "ModelExprRange.h"

namespace vsc {

ModelExprRange::ModelExprRange(
		bool			is_single,
		IModelExpr		*lower,
		IModelExpr		*upper) :
				m_is_single(is_single), m_lower(lower), m_upper(upper) {
	// TODO Auto-generated constructor stub

}

ModelExprRange::~ModelExprRange() {
	// TODO Auto-generated destructor stub
}

int32_t ModelExprRange::width() const {
	if (m_upper) {
		if (m_upper->width() > m_lower->width()) {
			return m_upper->width();
		} else {
			return m_lower->width();
		}
	} else {
		return m_lower->width();
	}
}

void ModelExprRange::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprRange::eval\n");
}

} /* namespace vsc */

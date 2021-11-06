/*
 * ModelExprRange.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#include "ModelExprRange.h"

namespace vsc {

ModelExprRange::ModelExprRange(
		ModelExpr		*lower,
		ModelExpr		*upper) : m_lower(lower), m_upper(upper) {
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

} /* namespace vsc */

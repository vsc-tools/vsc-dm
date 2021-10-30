/*
 * ModelExprPartSelect.cpp
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#include "ModelExprPartSelect.h"

namespace vsc {

ModelExprPartSelect::ModelExprPartSelect(
		ModelExpr				*lhs,
		int32_t					upper,
		int32_t					lower) :
				m_lhs(lhs), m_upper(upper), m_lower(lower) {

}

ModelExprPartSelect::~ModelExprPartSelect() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

/*
 * ModelExprIn.cpp
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#include "ModelExprIn.h"

namespace vsc {

ModelExprIn::ModelExprIn(
		ModelExpr			*lhs,
		ModelExprRangelist	*rangelist) : m_lhs(lhs), m_rangelist(rangelist) {

}

ModelExprIn::~ModelExprIn() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

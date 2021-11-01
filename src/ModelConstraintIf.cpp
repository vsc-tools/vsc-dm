/*
 * ModelConstraintIf.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#include "ModelConstraintIf.h"

namespace vsc {

ModelConstraintIf::ModelConstraintIf(
		ModelExpr			*cond,
		ModelConstraint		*true_c,
		ModelConstraint		*false_c) :
				m_cond(cond), m_true_c(true_c), m_false_c(false_c) {

}

ModelConstraintIf::~ModelConstraintIf() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

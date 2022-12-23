/*
 * ModelConstraintIfElse.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#include "ModelConstraintIfElse.h"

namespace vsc {
namespace dm {

ModelConstraintIfElse::ModelConstraintIfElse(
		IModelExpr			*cond,
		IModelConstraint	*true_c,
		IModelConstraint	*false_c) :
				m_cond(cond), m_true_c(true_c), m_false_c(false_c) {

}

ModelConstraintIfElse::~ModelConstraintIfElse() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

/*
 * ModelConstraintScope.cpp
 *
 *  Created on: Oct 22, 2021
 *      Author: mballance
 */

#include "ModelConstraintScope.h"

namespace vsc {

ModelConstraintScope::ModelConstraintScope() {
	// TODO Auto-generated constructor stub

}

ModelConstraintScope::~ModelConstraintScope() {
	// TODO Auto-generated destructor stub
}

void ModelConstraintScope::add_constraint(ModelConstraint *c) {
	m_constraints.push_back(ModelConstraintUP(c));
}

} /* namespace vsc */

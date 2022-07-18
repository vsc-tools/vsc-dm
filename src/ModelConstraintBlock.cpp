/*
 * ModelConstraintBlock.cpp
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#include "ModelConstraintBlock.h"

namespace vsc {

ModelConstraintBlock::ModelConstraintBlock(const std::string &name) :
		m_name(name) {

}

ModelConstraintBlock::~ModelConstraintBlock() {
	// TODO Auto-generated destructor stub
}

void ModelConstraintBlock::addConstraint(IModelConstraint *c) {
	m_constraints.push_back(IModelConstraintUP(c));
}

} /* namespace vsc */

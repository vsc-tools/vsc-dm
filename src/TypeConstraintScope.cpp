/*
 * TypeConstraintScope.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#include "TypeConstraintScope.h"

namespace vsc {
namespace dm {

TypeConstraintScope::TypeConstraintScope() {
	// TODO Auto-generated constructor stub

}

TypeConstraintScope::~TypeConstraintScope() {
	// TODO Auto-generated destructor stub
}

void TypeConstraintScope::addConstraint(
    ITypeConstraint         *c,
    bool                    owned) {
	m_constraints.push_back(ITypeConstraintUP(c, owned));
}

std::vector<ITypeVarUP> TypeConstraintScope::m_null;

}
} /* namespace vsc */


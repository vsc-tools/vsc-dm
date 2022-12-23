/*
 * ModelConstraintImplies.cpp
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#include "ModelConstraintImplies.h"

namespace vsc {
namespace dm {

ModelConstraintImplies::ModelConstraintImplies(
		IModelExpr			*cond,
		IModelConstraint	*body) : m_cond(cond), m_body(body) {
	// TODO Auto-generated constructor stub

}

ModelConstraintImplies::~ModelConstraintImplies() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

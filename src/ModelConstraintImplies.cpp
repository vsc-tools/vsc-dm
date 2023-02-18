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
		IModelConstraint	*body,
        bool                cond_owned,
        bool                body_owned) : 
            m_cond(cond, cond_owned), m_body(body, body_owned) {
	// TODO Auto-generated constructor stub

}

ModelConstraintImplies::~ModelConstraintImplies() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

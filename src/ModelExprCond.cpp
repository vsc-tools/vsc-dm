/*
 * ModelExprCond.cpp
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#include "ModelExprCond.h"

namespace vsc {
namespace dm {

ModelExprCond::ModelExprCond(
		IModelExpr		*cond,
		IModelExpr		*true_e,
		IModelExpr		*false_e) :
			m_cond(cond), m_true_e(true_e), m_false_e(false_e) {
	m_width = (true_e->width()>false_e->width())?true_e->width():false_e->width();
}

ModelExprCond::~ModelExprCond() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

/*
 * ModelExprVecSubscript.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#include "ModelExprVecSubscript.h"

namespace vsc {

ModelExprVecSubscript::ModelExprVecSubscript(
		ModelExpr			*expr,
		ModelExpr			*subscript)
				: m_expr(expr), m_subscript(subscript) {

}

ModelExprVecSubscript::~ModelExprVecSubscript() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

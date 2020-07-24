/*
 * ExprValLiteral.cpp
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#include "ExprValLiteral.h"

namespace vsc {

ExprValLiteral::ExprValLiteral(ExprVal *val) : m_val(val) {

}

ExprValLiteral::ExprValLiteral(ExprValSP val) : m_val(val) {

}

ExprValLiteral::~ExprValLiteral() {
	// TODO Auto-generated destructor stub
}

}


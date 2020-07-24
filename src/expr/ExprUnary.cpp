/*
 * ExprUnary.cpp
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#include "ExprUnary.h"

namespace vsc {

ExprUnary::ExprUnary(ExprUnaryOp op, ExprSP rhs) : m_op(op), m_rhs(rhs) {

}

ExprUnary::~ExprUnary() {
	// TODO Auto-generated destructor stub
}

}

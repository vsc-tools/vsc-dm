/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ModelExprBin.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#include "ModelExprBin.h"

namespace vsc {

ModelExprBin::ModelExprBin(
		ModelExpr			*lhs,
		BinOp				op,
		ModelExpr			*rhs) :
			m_lhs(lhs), m_op(op), m_rhs(rhs) {

	switch (op) {
	case BinOp::Eq:
	case BinOp::Ge:
	case BinOp::Le:
	case BinOp::Gt:
	case BinOp::Lt:
	case BinOp::Ne:
		m_width = 1;
		break;
	default:
		m_width = (lhs->width() > rhs->width())?lhs->width():rhs->width();
		break;
	}
}

ModelExprBin::~ModelExprBin() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */


/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * ExprEvaluator.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#include "sav/ExprNumericEvaluator.h"

#include <assert.h>

namespace vsc {

ExprNumericEvaluator::ExprNumericEvaluator() {
	// TODO Auto-generated constructor stub

}

ExprNumericEvaluator::~ExprNumericEvaluator() {
	// TODO Auto-generated destructor stub
}

#ifdef UNDEFINED
ExprValSP ExprNumericEvaluator::eval(Expr *e) {
	e->accept(this);
	return m_val;
}

ExprValNumericSP ExprNumericEvaluator::eval_num(Expr *e) {
	e->accept(this);
	return m_val;
}
#endif

void ExprNumericEvaluator::visitExprBin(ExprBin *e) {
#ifdef UNDEFINED
	ExprValSP lhs = _eval(e->lhs());
	ExprValSP rhs = _eval(e->rhs());

	// TODO: determine required argument types
	// - numeric
	// - boolean
	// - etc

	assert(lhs.get());
	assert(rhs.get());

	// TODO: for now, just assume both are Numeric
	ExprValInt *lhs_n = static_cast<ExprValInt *>(lhs.get());
	ExprValInt *rhs_n = static_cast<ExprValInt *>(rhs.get());

	switch (e->op()) {
    case BinOp_Eq:
    	m_val = lhs_n->eq(rhs_n)?ExprValInt::ONE:ExprValInt::ZERO;
    	break;
    case BinOp_Ne:
    	m_val = lhs_n->ne(rhs_n)?ExprValInt::ONE:ExprValInt::ZERO;
    	break;
    case BinOp_Gt:
    	m_val = lhs_n->gt(rhs_n)?ExprValInt::ONE:ExprValInt::ZERO;
    	break;
    case BinOp_Ge:
    	m_val = lhs_n->ge(rhs_n)?ExprValInt::ONE:ExprValInt::ZERO;
    	break;
    case BinOp_Lt:
    	m_val = lhs_n->lt(rhs_n)?ExprValInt::ONE:ExprValInt::ZERO;
    	break;
    case BinOp_Le:
    	m_val = lhs_n->le(rhs_n)?ExprValInt::ONE:ExprValInt::ZERO;
    	break;
    case BinOp_Add:
    	m_val = lhs_n->add(rhs_n);
    	break;
    case BinOp_Sub:
    	m_val = lhs_n->sub(rhs_n);
    	break;
    case BinOp_Div:
    	m_val = lhs_n->div(rhs_n);
    	break;
    case BinOp_Mul:
    	m_val = lhs_n->mul(rhs_n);
    	break;
    case BinOp_Mod:
    	m_val = lhs_n->mod(rhs_n);
    	break;
    case BinOp_And:
    	m_val = lhs_n->bit_and(rhs_n);
    	break;
    case BinOp_Or:
    	m_val = lhs_n->bit_or(rhs_n);
    	break;
    case BinOp_Sll:
    	m_val = lhs_n->sll(rhs_n);
    	break;
    case BinOp_Srl:
    	m_val = lhs_n->srl(rhs_n);
    	break;
    case BinOp_Xor:
    	m_val = lhs_n->bit_xor(rhs_n);
    	break;
	}
#endif
}

void ExprNumericEvaluator::visitExprFieldRef(ExprFieldRef *e) {
#ifdef UNDEFINED
	m_val = static_cast<FieldScalar *>(e->field())->val_num();
#endif
}

void ExprNumericEvaluator::visitExprValLiteral(ExprValLiteral *e) {
#ifdef UNDEFINED
	m_val = std::dynamic_pointer_cast<ExprValInt>(e->val());
#endif
}

ExprValSP ExprNumericEvaluator::_eval(ExprSP e) {
#ifdef UNDEFINED
	m_val.reset();
	e->accept(this);
	return m_val;
#endif
}



} /* namespace vsc */


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

#include "ExprNumericEvaluator.h"
#include <assert.h>

namespace vsc {

ExprNumericEvaluator::ExprNumericEvaluator() {
	// TODO Auto-generated constructor stub

}

ExprNumericEvaluator::~ExprNumericEvaluator() {
	// TODO Auto-generated destructor stub
}

ExprValSP ExprNumericEvaluator::eval(Expr *e) {
	e->accept(this);
	return m_val;
}

ExprValNumericSP ExprNumericEvaluator::eval_num(Expr *e) {
	e->accept(this);
	return m_val;
}

void ExprNumericEvaluator::visitExprBin(ExprBin *e) {
	fprintf(stdout, "--> lhs\n");
	ExprValSP lhs = _eval(e->lhs());
	fprintf(stdout, "<-- lhs\n");
	fprintf(stdout, "--> rhs\n");
	ExprValSP rhs = _eval(e->rhs());
	fprintf(stdout, "<-- rhs\n");

	// TODO: determine required argument types
	// - numeric
	// - boolean
	// - etc

	assert(lhs.get());
	assert(rhs.get());

	// TODO: for now, just assume both are Numeric
	ExprValNumeric *lhs_n = static_cast<ExprValNumeric *>(lhs.get());
	ExprValNumeric *rhs_n = static_cast<ExprValNumeric *>(rhs.get());

	switch (e->op()) {
    case BinOp_Eq:
    	m_val = lhs_n->eq(rhs_n)?ExprValNumeric::ONE:ExprValNumeric::ZERO;
    	break;
    case BinOp_Ne:
    	m_val = lhs_n->ne(rhs_n)?ExprValNumeric::ONE:ExprValNumeric::ZERO;
    	break;
    case BinOp_Gt:
    	m_val = lhs_n->gt(rhs_n)?ExprValNumeric::ONE:ExprValNumeric::ZERO;
    	break;
    case BinOp_Ge:
    	m_val = lhs_n->ge(rhs_n)?ExprValNumeric::ONE:ExprValNumeric::ZERO;
    	break;
    case BinOp_Lt:
    	m_val = lhs_n->lt(rhs_n)?ExprValNumeric::ONE:ExprValNumeric::ZERO;
    	break;
    case BinOp_Le:
    	m_val = lhs_n->le(rhs_n)?ExprValNumeric::ONE:ExprValNumeric::ZERO;
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
}

void ExprNumericEvaluator::visitExprFieldRef(ExprFieldRef *e) {
	m_val = static_cast<FieldScalar *>(e->field())->val_num();
	fprintf(stdout, "visitExprFieldRef: %p\n", m_val.get());
}

void ExprNumericEvaluator::visitExprNumericLiteral(ExprNumericLiteral *e) {
	m_val = e->val_num();
	fprintf(stdout, "visitExprNumericLiteral: %p\n", m_val.get());
}

ExprValSP ExprNumericEvaluator::_eval(ExprSP e) {
	m_val.reset();
	e->accept(this);
	return m_val;
}



} /* namespace vsc */

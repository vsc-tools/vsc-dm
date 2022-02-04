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
 * expr.cpp
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#include "attr_scalar.h"
#include "ctor.h"
#include "expr_base.h"
#include "ModelExprBin.h"
#include "ModelExprFieldRef.h"

namespace vsc {
namespace facade {

expr_base::expr_base() : m_core(0) { }

expr_base::expr_base(const attr_scalar &attr) :
		m_core(new ModelExprFieldRef(attr.field())) {
	ctor::inst()->push_expr(m_core);
}

expr_base::expr_base(const int_t &val) {
	m_core = val.toExpr();
	ctor::inst()->push_expr(m_core);
}

expr_base::expr_base(int32_t val) {
	DataTypeInt *dt = ctor::inst()->type_int(true, 32);
	ModelExprVal *e = new ModelExprVal(ModelVal(32, val));
	m_core = e;
	ctor::inst()->push_expr(m_core);
}

expr_base::expr_base(uint32_t val) {
	DataTypeInt *dt = ctor::inst()->type_int(false, 32);
	ModelExprVal *e = new ModelExprVal(ModelVal(32, val));
	m_core = e;
	ctor::inst()->push_expr(m_core);
}

expr_base::expr_base(int64_t val) {
	DataTypeInt *dt = ctor::inst()->type_int(true, 64);
	ModelExprVal *e = new ModelExprVal(ModelVal(64, val));
	m_core = e;
	ctor::inst()->push_expr(m_core);
}

expr_base::expr_base(uint64_t val) {
	DataTypeInt *dt = ctor::inst()->type_int(false, 64);
	ModelExprVal *e = new ModelExprVal(ModelVal(64, val));
	m_core = e;
	ctor::inst()->push_expr(m_core);
}

expr_base::~expr_base() {
	// TODO Auto-generated destructor stub
}

expr_base expr_base::operator == (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Eq,
					rhs.core()));
}

expr_base expr_base::operator != (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Ne,
					rhs.core()));
}

expr_base expr_base::operator < (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Lt,
					rhs.core()));
}

expr_base expr_base::operator > (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Gt,
					rhs.core()));
}

expr_base expr_base::operator <= (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Le,
					rhs.core()));
}

expr_base expr_base::operator >= (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Ge,
					rhs.core()));
}

expr_base expr_base::operator + (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Add,
					rhs.core()));
}

expr_base expr_base::operator - (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Sub,
					rhs.core()));
}

expr_base expr_base::operator && (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::LogAnd,
					rhs.core()));
}

expr_base expr_base::operator || (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::LogOr,
					rhs.core()));
}

expr_base expr_base::operator & (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::BinAnd,
					rhs.core()));
}

expr_base expr_base::operator | (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::BinOr,
					rhs.core()));
}

expr_base expr_base::operator ^ (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();

	return expr_base::mk(
			new ModelExprBin(
					m_core,
					BinOp::Xor,
					rhs.core()));
}

expr_base expr_base::mk(IModelExpr *core) {
	expr_base ret;
	ctor::inst()->push_expr(core);
	ret.m_core = core;
	return ret;
}

ModelVal expr_base::val() {
	return ModelVal(32);
}

/*
expr expr::operator == (int32_t v) {
	;
}
 */

} /* namespace facade */
} /* namespace vsc */

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
 * attr_scalar.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "attr_scalar.h"
#include "rand_obj.h"
#include "DataTypeInt.h"
#include "ModelExprFieldRef.h"
#include "ModelExprBin.h"
#include "ModelExprVal.h"
#include "ctor.h"

namespace vsc {
namespace facade {

attr_scalar::attr_scalar(
		bool				is_signed,
		int32_t				width,
		const int_t			&ival) {
	m_field = new ModelFieldRoot(new DataTypeInt(is_signed, width), m_name);

	if (m_parent) {
		// Model belongs to the parent scope
		static_cast<rand_obj *>(parent())->add_field(this);
	} else {
		// We own the field since there is no parent scope
		m_field_u = ModelFieldRootUP(m_field);
	}
}

attr_scalar::~attr_scalar() {
	// TODO Auto-generated destructor stub
}

expr attr_scalar::operator == (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Eq,
			rhs_e));
}

expr attr_scalar::operator == (const int_t &val) {
	ModelExprVal *rhs = val.toExpr();
	ModelExprBin *eq = new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Eq,
			rhs);
	return expr(eq);
}

//expr attr_scalar::operator == (uint64_t val) {
//	;
//}

expr attr_scalar::operator != (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Ne,
			rhs_e));
}

expr attr_scalar::operator != (const int_t &val) {
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Eq,
			val.toExpr()));
}

expr attr_scalar::operator < (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Lt,
			rhs_e));
}

expr attr_scalar::operator < (const int_t &val) {
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Lt,
			val.toExpr()));
}


expr attr_scalar::operator > (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Gt,
			rhs_e));
}

expr attr_scalar::operator > (const int_t &val) {
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Gt,
			val.toExpr()));
}


expr attr_scalar::operator <= (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Le,
			rhs_e));
}

expr attr_scalar::operator <= (const int_t &val) {
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Le,
			val.toExpr()));
}

expr attr_scalar::operator >= (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Ge,
			rhs_e));
}

expr attr_scalar::operator >= (const int_t &val) {
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Ge,
			val.toExpr()));
}

uint32_t attr_scalar::u32() {
	return field()->val().u32();
}

int32_t attr_scalar::i32() {
	return field()->val().i32();
}

uint64_t attr_scalar::u64() {
	return field()->val().u64();
}

int64_t attr_scalar::i64() {
	return field()->val().i64();
}

void attr_scalar::val_s(int64_t v) {
	;
}

void attr_scalar::val_u(uint64_t v) {
	;
}


} /* namespace facade */
} /* namespace vsc */

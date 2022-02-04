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
#include "Debug.h"
#include "ModelExprFieldRef.h"
#include "ModelExprBin.h"
#include "ModelExprVal.h"
#include "ctor.h"

#undef EN_DEBUG_ATTR_SCALAR

#ifdef EN_DEBUG_ATTR_SCALAR
#define DEBUG_ENTER(fmt, ...) \
	DEBUG_ENTER_BASE(attr_scalar, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
	DEBUG_LEAVE_BASE(attr_scalar, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
	DEBUG_BASE(attr_scalar, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif


namespace vsc {
namespace facade {

attr_scalar::attr_scalar(
		bool				is_signed,
		int32_t				width,
		const int_t			&ival,
		bool				parentless) : m_is_signed(is_signed), m_width(width) {
	DEBUG_ENTER("attr_scalar()");
	m_field = new ModelFieldRoot(
			ctor::inst()->type_int(is_signed, width),
			m_name);
	fprintf(stdout, "attr_scalar::attr_scalar ival.bits=%d\n", ival.toVal().bits());
	ModelVal ival_v = ival.toVal();
	m_field->val()->set(&ival_v);

	/*
	if (m_parent && !parentless) {
		// Model belongs to the parent scope
		fprintf(stdout, "field %s has a parent\n", m_name.c_str());
		static_cast<rand_obj *>(parent())->add_field(this);
	} else {
		// We own the field since there is no parent scope
		fprintf(stdout, "field %s has no parent\n", m_name.c_str());
		m_field_u = ModelFieldUP(m_field);
	}
	 */
	DEBUG_LEAVE("attr_scalar()");
}

attr_scalar::~attr_scalar() {
	// TODO Auto-generated destructor stub
}

void attr_scalar::build() {
	DEBUG_ENTER("build(phase=%d)", ctor::inst()->build_phase());
	if (ctor::inst()->build_phase() == 0) {
		if (ctor::inst()->build_field()) {
			ctor::inst()->build_field()->add_field(m_field);
		} else {
			m_field_u = ModelFieldUP(m_field);
		}
	}
	DEBUG_LEAVE("build(phase=%d)", ctor::inst()->build_phase());
}

expr_base attr_scalar::operator ()() {
	return expr_base::mk(new ModelExprFieldRef(field()));
}

/*
expr_base attr_scalar::operator == (const expr_base &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Eq,
			rhs_e));
}

//expr attr_scalar::operator == (uint64_t val) {
//	;
//}

expr_base attr_scalar::operator != (const expr_base &rhs) {
	DEBUG_ENTER("operator !=");
	ctor::inst()->pop_expr();
	DEBUG_LEAVE("operator !=");
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Ne,
			rhs.core()));
}

expr_base attr_scalar::operator < (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Lt,
			rhs.core()));
}

expr_base attr_scalar::operator > (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Gt,
			rhs.core()));
}

expr_base attr_scalar::operator <= (const expr_base &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Le,
			rhs_e));
}

expr_base attr_scalar::operator >= (const expr_base &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Ge,
			rhs_e));
}

expr_base attr_scalar::operator % (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ModelExpr *rhs_e = rhs.core();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Mod,
			rhs_e));
}

expr_base attr_scalar::operator + (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Add,
			rhs.core()));
}

expr_base attr_scalar::operator - (const expr_base &rhs) {
	ctor::inst()->pop_expr();
	return expr_base::mk(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Sub,
			rhs.core()));
}
 */

uint32_t attr_scalar::u32() {
	return field()->val()->val_u();
}

int32_t attr_scalar::i32() {
	return field()->val()->val_i();
}

uint64_t attr_scalar::u64() {
	return field()->val()->val_u();
}

int64_t attr_scalar::i64() {
	return field()->val()->val_i();
}

void attr_scalar::val_s(int64_t v) {
	field()->val()->val_u(v, m_width);
}

int64_t attr_scalar::val_s() const {
	return field()->val()->val_i();
}

void attr_scalar::val_u(uint64_t v) {
	field()->val()->val_u(v, m_width);
}

uint64_t attr_scalar::val_u() const {
	return field()->val()->val_u();
}


} /* namespace facade */
} /* namespace vsc */

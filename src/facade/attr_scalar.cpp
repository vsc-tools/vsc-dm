/*
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
#include "ctor.h"

namespace vsc {
namespace facade {

attr_scalar::attr_scalar(
		bool				is_signed,
		int32_t				width) {
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

expr attr_scalar::operator != (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Ne,
			rhs_e));
}

expr attr_scalar::operator < (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Lt,
			rhs_e));
}

expr attr_scalar::operator > (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Gt,
			rhs_e));
}

expr attr_scalar::operator <= (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Le,
			rhs_e));
}

expr attr_scalar::operator >= (const expr &rhs) {
	ModelExpr *rhs_e = ctor::inst()->pop_expr();
	return expr(new ModelExprBin(
			new ModelExprFieldRef(field()),
			BinOp::Ge,
			rhs_e));
}

/*
expr attr_scalar::operator == (const attr_scalar &rhs) {
	return expr(new ModelExprFieldRef(rhs.field()));
}
 */

int64_t attr_scalar::val_s() {
	int64_t ret = 0;
}

uint64_t attr_scalar::val_u() {
	;
}

void attr_scalar::val_s(int64_t v) {
	;
}

void attr_scalar::val_u(uint64_t v) {
	;
}


} /* namespace facade */
} /* namespace vsc */

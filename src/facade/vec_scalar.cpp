/*
 * vec_scalar.cpp
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#include "ctor.h"
#include "rand_obj.h"
#include "vec_scalar.h"
#include "ModelExprFieldRef.h"
#include "ModelExprVecSubscript.h"
#include "ModelFieldVecRoot.h"

namespace vsc {
namespace facade {

vec_scalar::vec_scalar(
		bool			is_signed,
		int32_t			width,
		int32_t			isize) : size("size", true) {
	/*
	ctor::inst()->type_int(is_signed, width);
	ModelFieldVec *vec = new ModelFieldVecRoot(
			ctor::inst()->type_int(is_signed, width),
			m_name,
			size.release());
	m_field = vec;

	if (m_parent) {
		static_cast<rand_obj *>(parent())->add_field(this);
	} else {
		m_field_u = ModelFieldUP(m_field);
	}

	for (int32_t i=0; i<isize; i++) {
		vec->push_back(0);
	}
	 */
}

vec_scalar::~vec_scalar() {
	// TODO Auto-generated destructor stub
}

void vec_scalar::push_back(uint32_t v) {
	ModelFieldVec *vec = static_cast<ModelFieldVec *>(m_field);
	ModelFieldRoot *field = new ModelFieldRoot(
			vec->datatype(),
			"a");
	field->val().val_u(v);
	vec->push_back(field);
}

expr_base vec_scalar::subscript(const expr_base &rhs) {
	ctor::inst()->pop_expr();
	ModelExprVecSubscript *se = new ModelExprVecSubscript(
			new ModelExprFieldRef(field()),
			rhs.core());
	return expr_base::mk(se);
}

} /* namespace facade */
} /* namespace vsc */

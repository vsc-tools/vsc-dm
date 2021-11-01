/*
 * type_scalar.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#include "int_t.h"
#include "ctor.h"

namespace vsc {
namespace facade {

int_t::int_t(bool is_signed, int32_t width, uint64_t val) :
	m_is_signed(is_signed), m_width(width), m_val(val) {

}

int_t::int_t(int32_t val) :
	m_is_signed(true), m_width(32), m_val(val) {
}

int_t::int_t(int64_t val) :
	m_is_signed(true), m_width(64), m_val(val) {
}

ModelExprVal *int_t::toExpr() const {
	DataTypeInt *dt = ctor::inst()->type_int(m_is_signed, m_width);
	ModelExprVal *ret = new ModelExprVal(ModelVal(dt));
	// TODO:
	ret->val().push_word(m_val);
	return ret;
}

ModelVal int_t::toVal() const {
	// TODO:
	ModelVal ret(m_is_signed, m_width);
	ret.push_word(m_val);
	return ret;
}

} /* namespace facade */
} /* namespace vsc */

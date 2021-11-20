/*
 * type_scalar.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#include "int_t.h"
#include "ctor.h"
#include "Debug.h"

#undef EN_DEBUG_INT_T
#ifdef EN_DEBUG_INT_T
DEBUG_SCOPE(int_t);
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(int_t, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(int_t, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(int_t, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

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
	DEBUG_ENTER("toExpr width=%d is_signed=%d val=0x%llx", m_width, m_is_signed, m_val);
	DataTypeInt *dt = ctor::inst()->type_int(m_is_signed, m_width);
	ModelExprVal *ret = new ModelExprVal(ModelVal(m_width));
	// TODO:
	ret->val().u64(m_val);
	DEBUG_LEAVE("toExpr width=%d is_signed=%d val=0x%llx", m_width, m_is_signed, m_val);
	return ret;
}

ModelVal int_t::toVal() const {
	ModelVal ret(m_width);
	ret.u64(m_val);
	return ret;
}

} /* namespace facade */
} /* namespace vsc */

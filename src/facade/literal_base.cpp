/*
 * literal_base.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#include <stdio.h>
#include "literal_base.h"

namespace vsc {
namespace facade {

literal_base::literal_base(bool val) :
		m_is_signed(false), m_width(1), m_val(val) {
}

literal_base::literal_base(int32_t val) :
		m_is_signed(true), m_width(32), m_val(val) {
}

literal_base::literal_base(int64_t val) :
		m_is_signed(true), m_width(64), m_val(val) {
}

literal_base::literal_base(
		bool			is_signed,
		uint32_t		width,
		uint64_t		val) :
				m_is_signed(is_signed), m_width(width), m_val(val) {
}

literal_base::~literal_base() {
	// TODO Auto-generated destructor stub
}

ModelExprVal *literal_base::toExpr() const {
	ModelExprVal *ret = new ModelExprVal(ModelVal(32, m_val));
	return ret;
}

} /* namespace facade */
} /* namespace vsc */

/*
 * type_scalar.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include "ModelExprVal.h"

namespace vsc {
namespace facade {

class int_t {
public:
	int_t(bool is_signed, int32_t width, uint64_t v);

	int_t(int32_t val);

	int_t(int64_t val);

	ModelExprVal *toExpr() const;

	ModelVal toVal() const;

	uint64_t val() const { return m_val; }

private:
	bool			m_is_signed;
	uint32_t		m_width;
	uint64_t		m_val;
};

template <int W> class si_t : public int_t {
public:
	si_t(int64_t v) : int_t(true, W, v) { }
};

template <int W> class ui_t : public int_t {
public:
	ui_t(uint64_t v) : int_t(false, W, v) { }
};

} /* namespace facade */
} /* namespace vsc */


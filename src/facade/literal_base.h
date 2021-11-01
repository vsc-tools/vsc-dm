/*
 * literal_base.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include "ModelExprVal.h"

namespace vsc {
namespace facade {

class literal_base {
public:
	literal_base(bool val);

	literal_base(int32_t val);

	literal_base(int64_t val);

	literal_base(
			bool		is_signed,
			uint32_t	width,
			uint64_t	val);

	virtual ~literal_base();

	ModelExprVal *toExpr() const;

private:
	bool			m_is_signed;
	uint32_t		m_width;
	uint64_t		m_val;
};

template <int W> class si : public literal_base {
public:
	si(int64_t v) : literal_base(true, W, v) { }
};

template <int W> class ui : public literal_base {
public:
	ui(uint64_t v) : literal_base(true, W, v) { }
};

} /* namespace facade */
} /* namespace vsc */


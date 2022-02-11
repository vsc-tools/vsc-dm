/*
 * vec_scalar.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include "rand_attr.h"
#include "ModelFieldVecRoot.h"

namespace vsc {
namespace facade {

class vec_scalar : public attr_base {
public:
	vec_scalar(
			bool		is_signed,
			int32_t		width,
			int32_t		size);

	virtual ~vec_scalar();

	rand_attr<ui_t<32>>			size;

	void push_back(uint64_t v);

	expr_base subscript(const expr_base &rhs);

private:

};

} /* namespace facade */
} /* namespace vsc */


/*
 * vec_it_base.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include "expr_base.h"

namespace vsc {
namespace facade {

class vec_it_base {
public:
	vec_it_base(const expr_base &it);

	vec_it_base(uint32_t idx);

	virtual ~vec_it_base();
};

} /* namespace facade */
} /* namespace vsc */


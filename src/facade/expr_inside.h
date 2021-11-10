/*
 * expr_inside.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#pragma once
#include "expr_base.h"
#include "expr_rangelist.h"
#include <vector>

namespace vsc {
namespace facade {

expr_base (inside)(
		const expr_base				&cond,
		const expr_rangelist	&rangelist,
		const char				*file=0,
		int32_t					lineno=-1);

expr_base (inside)(
		const expr_base							&cond,
		std::initializer_list<expr_base>			rangelist,
		const char							*file=0,
		int32_t								lineno=-1);

expr_base (inside)(
		const expr_base						&cond,
		const std::vector<expr_range>		&rangelist,
		const char							*file=0,
		int32_t								lineno=-1);

/*
#define __unwrap(...) __VA_ARGS__
#define inside(cond, rng) \
	inside(cond, rng, __FILE__, __LINE__)
 */


} /* namespace facade */
} /* namespace vsc */


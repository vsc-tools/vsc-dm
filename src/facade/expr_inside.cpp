/*
 * expr_inside.cpp
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#include "ctor.h"
#include "expr_inside.h"
#include "ModelExprIn.h"
#include "ModelExprRangelist.h"

#undef inside

namespace vsc {
namespace facade {

expr (inside)(
		const expr				&cond,
		const expr_rangelist	&rangelist,
		const char				*file,
		int32_t					lineno) {
	/*
	std::vector<ModelExprRange *>	&ranges;

	ModelExprRangelist *rl_m = new ModelExprRangelist(ranges);
	 */

	return expr(0);
}

expr (inside)(
		const expr						&cond,
		std::initializer_list<expr>		rangelist,
		const char						*file,
		int32_t							lineno) {
	std::vector<ModelExprRange *>	ranges;
	for (auto it=rangelist.begin(); it!=rangelist.end(); it++) {
		ctor::inst()->pop_expr();
		ranges.push_back(new ModelExprRange(it->core(), 0));
	}
	ctor::inst()->pop_expr();
	ModelExpr *cond_m = cond.core();

	ModelExprRangelist *rl_m = new ModelExprRangelist(ranges);

	return expr(new ModelExprIn(cond_m, rl_m));
}

expr (inside)(
		const expr							&cond,
		std::initializer_list<expr_range>	rangelist,
		const char							*file,
		int32_t								lineno) {
	std::vector<ModelExprRange *>	ranges;
	for (auto it=rangelist.begin(); it!=rangelist.end(); it++) {
		ranges.push_back(it->core());
	}
	ctor::inst()->pop_expr();
	ModelExpr *cond_m = cond.core();

	ModelExprRangelist *rl_m = new ModelExprRangelist(ranges);

	return expr(new ModelExprIn(cond_m, rl_m));
}

} /* namespace facade */
} /* namespace vsc */

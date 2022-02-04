/*
 * expr_inside.cpp
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#include "expr_inside.h"

#include "ctor.h"
#include "ModelExprIn.h"
#include "ModelExprRangelist.h"

#undef inside

namespace vsc {
namespace facade {

expr_base (inside)(
		const expr_base				&cond,
		const expr_rangelist	&rangelist,
		const char				*file,
		int32_t					lineno) {
	/*
	std::vector<ModelExprRange *>	&ranges;

	ModelExprRangelist *rl_m = new ModelExprRangelist(ranges);
	 */

	return expr_base(0);
}

expr_base (inside)(
		const expr_base						&cond,
		std::initializer_list<expr_base>		rangelist,
		const char						*file,
		int32_t							lineno) {
	std::vector<IModelExprRange *>	ranges;
	for (auto it=rangelist.begin(); it!=rangelist.end(); it++) {
		ctor::inst()->pop_expr();
		ranges.push_back(new ModelExprRange(it->core(), 0));
	}
	ctor::inst()->pop_expr();
	IModelExpr *cond_m = cond.core();

	ModelExprRangelist *rl_m = new ModelExprRangelist(ranges);

	return expr_base::mk(new ModelExprIn(cond_m, rl_m));
}

expr_base (inside)(
		const expr_base						&cond,
		const std::vector<expr_range>		&rangelist,
		const char							*file,
		int32_t								lineno) {
	std::vector<IModelExprRange *>	ranges;
	for (auto it=rangelist.begin(); it!=rangelist.end(); it++) {
		// TODO: build elem/range as appropriate
//		ranges.push_back(it->core());
	}
	ctor::inst()->pop_expr();
	IModelExpr *cond_m = cond.core();

	ModelExprRangelist *rl_m = new ModelExprRangelist(ranges);

	return expr_base::mk(new ModelExprIn(cond_m, rl_m));
}

} /* namespace facade */
} /* namespace vsc */

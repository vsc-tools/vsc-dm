/*
 * expr_rangelist.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>

#include "expr_range.h"

namespace vsc {
namespace facade {

class expr_rangelist {
public:
	/*
	expr_rangelist(
			std::initializer_list<expr_range>	ranges);
			 */

	expr_rangelist(
			const std::vector<expr_range>	&ranges);

	virtual ~expr_rangelist();
};

} /* namespace facade */
} /* namespace vsc */


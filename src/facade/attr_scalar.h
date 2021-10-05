/*
 * attr_scalar.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "attr_base.h"
#include "expr.h"
#include "scope.h"
#include "ModelFieldRoot.h"

namespace vsc {
namespace facade {

class attr_scalar : public attr_base {
public:
	attr_scalar(
			bool				is_signed,
			int32_t				width);

	virtual ~attr_scalar();

	expr operator == (const expr &rhs);

	int64_t val_s();

	uint64_t val_u();

	void val_s(int64_t v);

	void val_u(uint64_t v);


};

} /* namespace facade */
} /* namespace vsc */


/*
 * vec_scalar.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>

namespace vsc {
namespace facade {

class vec_scalar {
public:
	vec_scalar(
			bool		is_signed,
			int32_t		width,
			int32_t		size);

	virtual ~vec_scalar();

private:

};

} /* namespace facade */
} /* namespace vsc */


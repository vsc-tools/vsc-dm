/*
 * attr.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "attr_scalar.h"
#include "expr.h"

namespace vsc {
namespace facade {

class rand_obj;

template <typename T> class attr : public attr_scalar {
public:
};

template <> class attr<int> : public attr_scalar {
public:

	attr(
			const scope			&s,
			int32_t 			width=32) : attr_scalar(true, width) {
	}

	expr operator == (int32_t v) {
//		return false;
	}

};


} /* namespace facade */
} /* namespace vsc */


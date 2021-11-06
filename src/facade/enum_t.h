/*
 * enum_t.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include "enum_t_base.h"

namespace vsc {
namespace facade {

template <typename T, T first, T last> class enum_t : public enum_t_base {
public:

	enum_t() : enum_t_base() {

	}

	// Could use variadic args for bag-of enums


};

}
}

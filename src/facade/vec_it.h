/*
 * vec_it.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include "vec_it_base.h"

namespace vsc {
namespace facade {

template <typename T> class vec_it {

};

class vec_it_idx {
public:
};

template <int W> class vec_it<ui_t<W>> : public vec_it_base {
public:
	vec_it(const expr_base &idx) : vec_it_base(idx) { }

	vec_it(uint32_t idx) : vec_it_base(idx) { }

	uint64_t operator ()() const {
		return 0;
	}

	void operator ()(uint64_t v) {

	}

};

}
}




/*
 * rand_vec.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include <functional>

#include "ctor.h"
#include "expr.h"
#include "int_t.h"
#include "scope.h"
#include "vec_cls.h"
#include "vec_it.h"
#include "vec_scalar.h"

namespace vsc {
namespace facade {

template <typename T> class rand_vec : public vec_cls {
public:

};

template <int W> class rand_vec<ui_t<W>> : public vec_scalar {
public:
	using c_iterator=int;
public:

	rand_vec(
			const scope		&name,
			int32_t			size=0) : vec_scalar(false, W, size) { }

	void foreach(
			const std::function<void(c_iterator &)> &body) {

	}

	void foreach(
			) {

	}

	expr<ui_t<W>> operator [](const expr_base &rhs) {
		expr<ui_t<W>>(subscript(rhs));
	}

};

}
}


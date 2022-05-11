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
//#include "expr_array_ref.h"
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

	rand_vec(
			const scope		&name,
			int32_t			size=0) : vec_scalar(false, W, size) { }

	void foreach(const std::function<void(const expr_base &i)> &body) {
		// TODO: push foreach constraint
		expr_base i; // TODO: construct from foreach 'idx' field
		body(i);
	}

	void foreach(
			) {

	}

	/*
	expr_array_ref<ui_t<W>> operator ()() {
		return expr_array_ref<ui_t<W>>();
	}
	 */

	/**
	 * Return a ref that is convertible to a value or expression
	 */
	vec_it<ui_t<W>> operator [](const expr_base &rhs) {
		return vec_it<ui_t<W>>(rhs);
	}

	/*
	vec_it<ui_t<W>> operator [](uint32_t idx) const {
		return vec_it<ui_t<W>>(idx);
	}
	 */

	/*
	uint64_t operator [](uint32_t idx) const {
		return 0; // TODO:
	}
	 */
private:

};

template <int W> class rand_vec<si_t<W>> : public vec_scalar {

};

}
}


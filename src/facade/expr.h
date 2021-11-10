/*
 * expr.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include "expr_base.h"
#include "int_t.h"

namespace vsc {
namespace facade {

template <class T> class expr : public expr_base {
public:

};

template <int W> class expr<ui_t<W>> : public expr_base {
public:

	expr(const expr_base &e) {
		m_core = e.core();
	}

	uint64_t operator ()() {
		return val().u64();
	}

};

}
}

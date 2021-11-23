/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * attr.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "attr_scalar.h"
#include "expr_base.h"
#include "int_t.h"

namespace vsc {
namespace facade {

class rand_obj;

template <typename T> class attr {
public:
	template <typename ...At> attr(
			const scope &name,
			At const &... args) {
		m_core = std::shared_ptr<T>(new T(name, args...));
	}

	std::shared_ptr<T> operator ->() {
		return m_core;
	}

	std::shared_ptr<T>			m_core;
};

template <int W> class attr<ui_t<W>> : public attr_scalar {
public:

	attr(
		const scope &s="__anonymous__",
		const int_t &ival=int_t(false, W, 0)) : attr_scalar(false, W, ival) {

	}

	uint64_t operator ()() { return u64(); }

	void operator ()(uint64_t v) {
		val_u(v);
	}

	void operator ()(const ui_t<W> &v) {
		fprintf(stdout, "operator<%d>()\n", W);
	}

	void operator = (const expr_base &rhs);

	attr_scalar *operator ->() const { return this; }

private:


};

template <int W> class attr<si_t<W>> : public attr_scalar {
public:

	attr(
			const scope &s="__anonymous__",
			const int_t &ival=int_t(true, W, 0)) : attr_scalar(true, W, ival) {
	}

	int64_t operator ()() { return i64(); }

	attr_scalar *operator ->() const { return this; }

private:


};


} /* namespace facade */
} /* namespace vsc */


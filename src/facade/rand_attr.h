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
 * rand_attr.h
 *
 *  Created on: Aug 10, 2021
 *      Author: mballance
 */

#pragma once
#include <type_traits>
#include "attr_cls.h"
#include "attr_scalar.h"
#include "enum_t.h"
#include "int_t.h"

namespace vsc {
namespace facade {

template <typename T> class rand_attr {
public:
	template <typename ...At> rand_attr(
			const scope &name,
			At const &... args) {
		m_core = std::shared_ptr<T>(new T(name, args...));
	}

	std::shared_ptr<T> operator -> () {
		return m_core;
	}

	std::shared_ptr<T>				m_core;
};

template <int W> class rand_attr<ui_t<W>> : public attr_scalar {
public:
	friend class vec_scalar;

	rand_attr(
			const scope &name,
			const int_t	&ival=int_t(false, W, 0)) :
				attr_scalar(false, W, ival) {
		m_field->setFlag(ModelFieldFlag::DeclRand);
	}

	uint64_t operator ()() const {
		return val_u();
	}

	void operator ()(uint64_t v) {
		return val_u(v);
	}

	/*
	template <typename = typename std::enable_if<(W<=8)>::type> void operator()(uint8_t v) {
		val_u(v);
	}
	 */

	/*
	template <typename = typename std::enable_if<(W>8 && W<=16)>::type> uint16_t operator ()() const {
		return val_u();
	}

	template <typename = typename std::enable_if<(W>8 && W<=16)>::type> void operator()(uint16_t v) {
		val_u(v);
	}

	template <typename = typename std::enable_if<(W>16 && W<=32)>::type> uint32_t operator ()() const {
		return val_u();
	}

	template <typename = typename std::enable_if<(W>16 && W<=32)>::type> void operator()(uint32_t v) {
		val_u(v);
	}

	template <typename = typename std::enable_if<(W>32 && W<=64)>::type> uint64_t operator ()() const {
		return val_u();
	}

	template <typename = typename std::enable_if<(W>32 && W<=64)>::type> void operator()(uint64_t v) {
		val_u(v);
	}
	 */

	const rand_attr<ui_t<W>> &operator = (uint64_t v) {
		val_u(v);
		return *this;
	}

	const rand_attr<ui_t<W>> &operator = (const rand_attr<ui_t<W>> &rhs) {
		val_u(rhs.val_u());
		return *this;
	}

	const rand_attr<ui_t<W>> &operator = (const attr_scalar &rhs) {
		val_u(rhs.val_u());
		return *this;
	}

	rand_attr<ui_t<W>> *operator -> () {
		return this;
	}

	/*
	void operator = (const attr_scalar &rhs) {
		val_u(rhs.val_u());
	}

	template <int Wt> void operator = (const rand_attr<ui_t<Wt>> &rhs) {
		val_u(rhs.val_u());
	}

	 */
	/*
	template <int Wt> void operator = (const rand_attr<si_t<Wt>> &rhs) {
		val_u(rhs.val_u());
	}
	 */

	/*
	void operator = (const attr_scalar &rhs) {
		val_u(rhs.val_u());
	}
	 */

private:

	rand_attr(
			const scope 	&name,
			bool			parentless) :
		attr_scalar(false, W, int_t(false, W, 0), parentless) {
		m_field->setFlag(ModelFieldFlag::DeclRand);
	}
};

template <int W> class rand_attr<si_t<W>> : public attr_scalar {
public:

	rand_attr(
			const scope &name,
			const int_t &ival=int_t(true, W, 0)) :
				attr_scalar(true, W, ival) {
		m_field->setFlag(ModelFieldFlag::DeclRand);
	}

	int64_t operator ()() const { return val_s(); }

	void operator ()(int64_t v) { val_s(v); }

	rand_attr<si_t<W>> *operator -> () {
		return this;
	}

	void operator = (int64_t v) {
		val_s(v);
	}

	const rand_attr<si_t<W>> &operator = (const rand_attr<si_t<W>> &rhs) {
		val_s(rhs.val_s());
		return *this;
	}

	const rand_attr<si_t<W>> &operator = (const attr_scalar &rhs) {
		val_s(rhs.val_s());
		return *this;
	}

};

template <typename T, T first, T last> class rand_attr<enum_t<T, first, last>> : public attr_scalar {
public:

	rand_attr(
			const scope &name) : attr_scalar(true, 32, int_t(true, 32, 0)) { }

	T operator ()() { return reinterpret_cast<T>(i64()); }
};

template <> class rand_attr<int> : public attr_scalar {
public:

	rand_attr(
			const scope		&name,
			const int_t		&ival=int_t(true, 32, 0)) :
				attr_scalar(true, 32, ival) {
		m_field->setFlag(ModelFieldFlag::DeclRand);
	}

	int32_t operator ()() { return i32(); }

	rand_attr<int> *operator ->() { return this; }
};

template <> class rand_attr<unsigned int> : public attr_scalar {
public:

	rand_attr(
			const scope		&name,
			const int_t		&ival=int_t(false, 32, 0)) :
				attr_scalar(false, 32, ival) {
		m_field->setFlag(ModelFieldFlag::DeclRand);
	}

	uint32_t operator ()() { return u32(); }

	rand_attr<unsigned int> *operator ->() { return this; }

};

}
}

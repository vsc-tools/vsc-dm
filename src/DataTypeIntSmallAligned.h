/*
 * DataTypeIntSmall.h
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#pragma once
#include "DataTypeInt.h"

namespace vsc {

/**
 * Operator implementation for <=32-bit types that are octet aligned
 */
template <typename T> class DataTypeIntSmallAligned : public DataTypeInt {
public:

	static_assert(sizeof(T) <= 32,
			"DataTypeIntSmall only handles types <=32-bit");

	virtual bool eq(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const override {
		return reinterpret_cast<T>(lhs.val(0)) == reinterpret_cast<T>(rhs.val(0));
	}

	virtual bool ge(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const override {
		if (!std::is_signed<T>) {
			return reinterpret_cast<T>(lhs.val(0)) >= reinterpret_cast<T>(rhs.val(0));
		} else {

		}
	}

	virtual bool gt(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const override {
		return reinterpret_cast<T>(lhs.val(0)) > reinterpret_cast<T>(rhs.val(0));
	}

	virtual bool le(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const override {
		return reinterpret_cast<T>(lhs.val(0)) <= reinterpret_cast<T>(rhs.val(0));
	}

	virtual bool lt(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const override {
		return reinterpret_cast<T>(lhs.val(0)) < reinterpret_cast<T>(rhs.val(0));
	}

};

}

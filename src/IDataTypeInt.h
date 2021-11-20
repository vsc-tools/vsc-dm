/*
 * IDataTypeInt.h
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelVal.h"

namespace vsc {

class IDataTypeInt {
public:

	virtual ~IDataTypeInt() { }

	virtual bool eq(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const = 0;

	virtual bool ge(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const = 0;

	virtual bool gt(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const = 0;

	virtual bool le(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const = 0;

	virtual bool lt(
			const ModelVal		&lhs,
			const ModelVal		&rhs) const = 0;
};


}





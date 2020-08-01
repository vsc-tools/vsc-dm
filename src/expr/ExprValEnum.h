/*
 * ExprValEnum.h
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#pragma once
#include "expr/ExprVal.h"
#include "datamodel/EnumTypeInfo.h"

namespace vsc {

class ExprValEnum : public ExprVal {
public:
	ExprValEnum(
			EnumTypeInfo		*info,
			int64_t				val);

	ExprValEnum();

	virtual ~ExprValEnum();

	const EnumTypeInfo *info() const { return m_info; }

	int64_t val() const { return m_val; }

private:
	EnumTypeInfo				*m_info;
	int64_t						m_val;
};

} /* namespace vsc */


/*
 * ExprValEnum.h
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#pragma once
#include "sav/EnumTypeInfo.h"
#include "sav/ExprVal.h"

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

	virtual std::string toString() const;

	virtual void accept(IVisitor *v) { v->visitExprValEnum(this); }

private:
	EnumTypeInfo				*m_info;
	int64_t						m_val;
};

} /* namespace vsc */


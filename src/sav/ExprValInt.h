/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * ExprValNumeric.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "sav/ExprVal.h"

namespace vsc {

class ExprValInt;
typedef std::shared_ptr<ExprValInt> ExprValIntUP;
typedef std::unique_ptr<ExprValInt> ExprValNumericUP;

class ExprValInt : public ExprVal {
public:
	ExprValInt();

	ExprValInt(
			uint64_t 	val,
			uint32_t 	width,
			bool 		is_signed);

	virtual ~ExprValInt();

	virtual uint64_t val_u() const {
		return m_val;
	}

	virtual int64_t val_s() const {
		return static_cast<int64_t>(m_val);
	}

	uint32_t width() const { return m_width; }

	bool is_signed() const { return m_is_signed; }

	virtual void val(uint64_t v) { m_val = v; }

	virtual bool eq(ExprValSP rhs) override;

	virtual bool eq(ExprVal *rhs) override;

	virtual bool ne(ExprValSP rhs) override;

	virtual bool ne(ExprVal *rhs) override;

	virtual bool gt(ExprValInt *rhs);

	virtual bool ge(ExprValInt *rhs);

	virtual bool lt(ExprValInt *rhs);

	virtual bool le(ExprValInt *rhs);

	ExprValIntUP add(const ExprValIntUP &rhs) const;

	ExprValIntUP sub(const ExprValIntUP &rhs) const;

	ExprValIntUP div(const ExprValInt &rhs) const;

	ExprValIntUP mul(const ExprValInt &rhs) const;

	ExprValIntUP mod(const ExprValInt &rhs) const;

	ExprValIntUP bit_and(const ExprValIntUP &rhs) const;

	ExprValIntUP bit_or(const ExprValIntUP &rhs) const;

	ExprValIntUP bit_xor(const ExprValIntUP &rhs) const;

	ExprValIntUP sll(const ExprValIntUP &rhs) const;

	ExprValIntUP srl(const ExprValIntUP &rhs) const;

	virtual std::string toString() const;

	virtual void accept(IVisitor *v) { v->visitExprValNumeric(this); }

	static ExprValIntUP mk(uint64_t val, uint32_t width, bool is_signed);

	static ExprValIntUP			ZERO;
	static ExprValIntUP			ONE;

private:
	uint64_t		m_val;
	uint64_t		*m_val_ext;
	uint32_t		m_width;
	bool			m_is_signed;
};

typedef std::shared_ptr<ExprValInt> ExprValIntUP;


} /* namespace vsc */


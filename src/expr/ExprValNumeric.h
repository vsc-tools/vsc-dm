
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
#include "expr/ExprVal.h"

namespace vsc {

class ExprValNumeric;
typedef std::shared_ptr<ExprValNumeric> ExprValNumericSP;

class ExprValNumeric : public ExprVal {
public:
	ExprValNumeric();

	ExprValNumeric(
			uint64_t 	val,
			uint32_t 	width,
			bool 		is_signed);

	virtual ~ExprValNumeric();

	virtual uint64_t val_u() const {
		return m_val;
	}

	virtual int64_t val_s() const {
		return static_cast<int64_t>(m_val);
	}

	uint32_t width() const { return m_width; }

	bool is_signed() const { return m_is_signed; }

	virtual void val(uint64_t v) { m_val = v; }

	virtual bool eq(ExprValNumeric *rhs);

	virtual bool ne(ExprValNumeric *rhs);

	virtual bool gt(ExprValNumeric *rhs);

	virtual bool ge(ExprValNumeric *rhs);

	virtual bool lt(ExprValNumeric *rhs);

	virtual bool le(ExprValNumeric *rhs);

	virtual ExprValNumericSP add(ExprValNumeric *rhs);

	virtual ExprValNumericSP sub(ExprValNumeric *rhs);

	virtual ExprValNumericSP div(ExprValNumeric *rhs);

	virtual ExprValNumericSP mul(ExprValNumeric *rhs);

	virtual ExprValNumericSP mod(ExprValNumeric *rhs);

	virtual ExprValNumericSP bit_and(ExprValNumeric *rhs);

	virtual ExprValNumericSP bit_or(ExprValNumeric *rhs);

	virtual ExprValNumericSP bit_xor(ExprValNumeric *rhs);

	virtual ExprValNumericSP sll(ExprValNumeric *rhs);

	virtual ExprValNumericSP srl(ExprValNumeric *rhs);

	static ExprValNumericSP			ZERO;
	static ExprValNumericSP			ONE;

private:
	uint64_t		m_val;
	uint32_t		m_width;
	bool			m_is_signed;
};

typedef std::shared_ptr<ExprValNumeric> ExprValNumericSP;


} /* namespace vsc */


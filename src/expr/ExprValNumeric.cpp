
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
 * ExprValNumeric.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "ExprValNumeric.h"

namespace vsc {

ExprValNumeric::ExprValNumeric() : ExprVal(ValType_Numeric),
		m_val(0), m_width(32), m_is_signed(true) {

}

ExprValNumeric::ExprValNumeric(
		uint64_t 	val,
		uint32_t	width,
		bool 		is_signed) : ExprVal(ValType_Numeric),
		m_val(val), m_width(width), m_is_signed(is_signed) {
	// TODO Auto-generated constructor stub

}

ExprValNumeric::~ExprValNumeric() {
	// TODO Auto-generated destructor stub
}

bool ExprValNumeric::eq(ExprValNumeric *rhs) {
	return m_val == rhs->m_val;
}

bool ExprValNumeric::ne(ExprValNumeric *rhs) {
	return m_val != rhs->m_val;
}

bool ExprValNumeric::gt(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() > rhs->val_s();
	} else {
		return val_u() > rhs->val_u();
	}
}

bool ExprValNumeric::ge(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() >= rhs->val_s();
	} else {
		return val_u() >= rhs->val_u();
	}
}

bool ExprValNumeric::lt(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() < rhs->val_s();
	} else {
		return val_u() < rhs->val_u();
	}
}

bool ExprValNumeric::le(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() <= rhs->val_s();
	} else {
		return val_u() <= rhs->val_u();
	}
}

ExprValNumericSP ExprValNumeric::add(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() + rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() + rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::sub(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() - rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() - rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::div(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() / rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() / rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::mul(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() * rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() * rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::mod(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() % rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() % rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::bit_and(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() & rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() & rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::bit_or(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() | rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() | rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::bit_xor(ExprValNumeric *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValNumeric(
				val_s() ^ rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValNumeric(
				val_u() ^ rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValNumeric::sll(ExprValNumeric *rhs) {
	return ExprValNumericSP(new ExprValNumeric(
			val_u() << rhs->val_u(),
			(rhs->width()>width())?rhs->width():width(),
			false));
}

ExprValNumericSP ExprValNumeric::srl(ExprValNumeric *rhs) {
	return ExprValNumericSP(new ExprValNumeric(
			val_u() >> rhs->val_u(),
			(rhs->width()>width())?rhs->width():width(),
			false));
}

ExprValNumericSP ExprValNumeric::ZERO(new ExprValNumeric(0, 8, true));
ExprValNumericSP ExprValNumeric::ONE(new ExprValNumeric(1, 8, true));


} /* namespace vsc */

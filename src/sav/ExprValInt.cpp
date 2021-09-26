
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

#include "sav/ExprValInt.h"

namespace vsc {

ExprValInt::ExprValInt() : ExprVal(ValType_Numeric),
		m_val(0), m_width(32), m_is_signed(true) {

}

ExprValInt::ExprValInt(
		uint64_t 	val,
		uint32_t	width,
		bool 		is_signed) : ExprVal(ValType_Numeric),
		m_val(val), m_width(width), m_is_signed(is_signed) {
	// TODO Auto-generated constructor stub

}

ExprValInt::~ExprValInt() {
	// TODO Auto-generated destructor stub
}

bool ExprValInt::eq(ExprValSP rhs) {
	return (rhs->type() == ValType_Numeric &&
			m_val == static_cast<ExprValInt *>(rhs.get())->m_val);
}

bool ExprValInt::eq(ExprVal *rhs) {
	return (rhs->type() == ValType_Numeric &&
			m_val == static_cast<ExprValInt *>(rhs)->m_val);
}

bool ExprValInt::ne(ExprValSP rhs) {
	return (rhs->type() == ValType_Numeric &&
			m_val != static_cast<ExprValInt *>(rhs.get())->m_val);
}

bool ExprValInt::ne(ExprVal *rhs) {
	return (rhs->type() == ValType_Numeric &&
			m_val != static_cast<ExprValInt *>(rhs)->m_val);
}

bool ExprValInt::gt(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() > rhs->val_s();
	} else {
		return val_u() > rhs->val_u();
	}
}

bool ExprValInt::ge(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() >= rhs->val_s();
	} else {
		return val_u() >= rhs->val_u();
	}
}

bool ExprValInt::lt(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() < rhs->val_s();
	} else {
		return val_u() < rhs->val_u();
	}
}

bool ExprValInt::le(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return val_s() <= rhs->val_s();
	} else {
		return val_u() <= rhs->val_u();
	}
}

ExprValNumericSP ExprValInt::add(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() + rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() + rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::sub(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() - rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() - rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::div(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() / rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() / rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::mul(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() * rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() * rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::mod(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() % rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() % rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::bit_and(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() & rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() & rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::bit_or(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() | rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() | rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::bit_xor(ExprValInt *rhs) {
	if (m_is_signed && rhs->m_is_signed) {
		return ExprValNumericSP(new ExprValInt(
				val_s() ^ rhs->val_s(),
				(rhs->width()>width())?rhs->width():width(),
				true));
	} else {
		return ExprValNumericSP(new ExprValInt(
				val_u() ^ rhs->val_u(),
				(rhs->width()>width())?rhs->width():width(),
				false));
	}
}

ExprValNumericSP ExprValInt::sll(ExprValInt *rhs) {
	return ExprValNumericSP(new ExprValInt(
			val_u() << rhs->val_u(),
			(rhs->width()>width())?rhs->width():width(),
			false));
}

ExprValNumericSP ExprValInt::srl(ExprValInt *rhs) {
	return ExprValNumericSP(new ExprValInt(
			val_u() >> rhs->val_u(),
			(rhs->width()>width())?rhs->width():width(),
			false));
}

std::string ExprValInt::toString() const {
	char tmp[32];
	sprintf(tmp, "%lld", m_val);
	return tmp;
}

ExprValNumericSP ExprValInt::mk(uint64_t val, uint32_t width, bool is_signed) {
	return ExprValNumericSP(new ExprValInt(val, width, is_signed));
}

ExprValNumericSP ExprValInt::ZERO(new ExprValInt(0, 8, true));
ExprValNumericSP ExprValInt::ONE(new ExprValInt(1, 8, true));


} /* namespace vsc */

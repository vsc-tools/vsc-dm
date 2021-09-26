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
 * ExprVal.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include <memory>
#include <vector>

#include "../IAccept.h"

namespace vsc {

enum class ExprValKind {
	Bool,
	Enum,
	IntU,
	IntS
};

class ExprVal;
typedef std::shared_ptr<ExprVal> ExprValSP;
typedef std::unique_ptr<ExprVal> ExprValUP;

/**
 * Values are always presented in integral form.
 * Sort data may be associated with values to assist
 * in formatting them properly
 */
class ExprVal {
public:
	ExprVal(
			ExprValKind kind,
			int32_t 	width=32);

	~ExprVal();

	ExprValKind kind() const { return m_kind; }

	bool eq(ExprVal *o) const;

	bool ne(ExprVal *o) const;

	std::string toString(uint8_t base=10) const;

	void resize(int32_t width);

	uint64_t val_u() const;

	int64_t val_s() const;

private:
	ExprValKind					m_kind;
	std::vector<uint32_t>		m_value;

	// Used by the val pool
	ExprVal						*m_next;

	int32_t						m_width;
	bool						m_is_signed;

};


} /* namespace vsc */


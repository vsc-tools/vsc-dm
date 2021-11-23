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
 * attr_scalar.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "attr_base.h"
#include "expr_base.h"
#include "int_t.h"
#include "scope.h"
#include "ModelFieldRoot.h"

namespace vsc {
namespace facade {

class attr_scalar : public attr_base {
public:
	attr_scalar(
			bool				is_signed,
			int32_t				width,
			const int_t			&ival,
			bool				parentless=false);

	virtual ~attr_scalar();

	virtual void build() override;

	expr_base operator ()();

//	void operator = (const expr_base &rhs);

	/*
	expr_base operator == (const expr_base &rhs);

	expr_base operator != (const expr_base &rhs);

	expr_base operator < (const expr_base &rhs);

	expr_base operator > (const expr_base &rhs);

	expr_base operator <= (const expr_base &rhs);

	expr_base operator >= (const expr_base &rhs);

	expr_base operator % (const expr_base &rhs);

	expr_base operator + (const expr_base &rhs);

	expr_base operator - (const expr_base &rhs);
	 */

//	expr operator == (const attr_scalar &rhs);

	uint32_t u32();

	int32_t i32();

	uint64_t u64();

	int64_t i64();

	void val_s(int64_t v);

	int64_t val_s() const;

	void val_u(uint64_t v);

	uint64_t val_u() const;


protected:
	bool					m_is_signed;
	int32_t					m_width;

};

} /* namespace facade */
} /* namespace vsc */


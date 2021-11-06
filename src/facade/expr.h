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
 * expr.h
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include "ModelExpr.h"
#include "int_t.h"

namespace vsc {

class ModelExpr;
using ModelExprUP=std::unique_ptr<ModelExpr>;
namespace facade {

class attr_scalar;

class expr {
	friend class attr_scalar;
public:
	expr(const attr_scalar &);

	expr(const int_t &);

	expr(int32_t v);

	expr(int64_t v);

	explicit expr(ModelExpr *core);

	virtual ~expr();

	ModelExpr *core() const { return m_core; }

private:

private:
//	ModelExprUP					m_core;
	ModelExpr					*m_core;
};

} /* namespace facade */
} /* namespace vsc */


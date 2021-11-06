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
 * ctor.h
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "ctor_ctxt.h"
#include "DataTypeInt.h"
#include "ModelConstraintScope.h"
#include "ModelExpr.h"
#include "RandState.h"

namespace vsc {

class ModelField;

namespace facade {

class rand_obj;
class attr_base;

class ctor {
public:
	ctor();

	virtual ~ctor();

	static ctor *inst();

	static void reset();

	ModelField *model_scope();

	std::string scope_name();

	rand_obj *scope(attr_base *s=0);

	void scope_ctor(
			const std::string			&name,
			rand_obj					*scope,
			const std::type_info		*ti);

	void scope_dtor(
			const std::string			&name,
			rand_obj					*scope,
			const std::type_info		*ti);

	uint32_t scope_depth() const { return m_scope_s.size(); }

	void push_expr_mode(bool expr_mode=true);

	bool is_expr_mode() const;

	void pop_expr_mode();

	void push_expr(ModelExpr *e);

	ModelExpr *expr();

	ModelExpr *pop_expr();

	uint32_t expr_depth() const { return m_expr_s.size(); }

	void push_constraint_scope(ModelConstraintScope *s);

	ModelConstraintScope *constraint_scope() const {
		return m_constraint_scope_s.back();
	}

	ModelConstraintScope *pop_constraint_scope();

	DataTypeInt *type_int(
			bool		is_signed,
			int32_t		width);

	/**
	 * Derives a randstate from the master copy
	 */
	RandState *mk_randstate();

private:
	std::vector<ModelExprUP>					m_expr_s;
	std::vector<ctor_ctxt_up>					m_scope_s;
	std::vector<bool>							m_expr_mode;
	std::unordered_map<int32_t, DataTypeIntUP>	m_si_type_m;
	std::unordered_map<int32_t, DataTypeIntUP>	m_ui_type_m;
	std::vector<ModelConstraintScope *>			m_constraint_scope_s;
	RandState									m_randstate;
	static std::unique_ptr<ctor>				m_inst;

};

} /* namespace facade */
} /* namespace vsc */


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
#include "obj.h"
#include "vsc/IModelExpr.h"
#include "DataTypeInt.h"
#include "ModelConstraintScope.h"
#include "ModelExpr.h"
#include "RandState.h"

namespace vsc {

class ModelField;

namespace facade {

class ctor {
public:
	ctor();

	virtual ~ctor();

	static ctor *inst();

	static void reset();

	ModelField *model_scope();

	std::string scope_name();

	obj *scope(obj *s=0);

	void scope_ctor(
			const std::string			&name,
			obj							*scope,
			const std::type_info		*ti);

	void scope_dtor(
			const std::string			&name,
			obj							*scope,
			const std::type_info		*ti);

	uint32_t scope_depth() const { return m_scope_s.size(); }

	void push_expr_mode(bool expr_mode=true);

	bool is_expr_mode() const;

	void pop_expr_mode();

	void push_expr(IModelExpr *e);

	IModelExpr *expr();

	IModelExpr *pop_expr();

	uint32_t expr_depth() const { return m_expr_s.size(); }

	void push_constraint_scope(IModelConstraintScope *s);

	IModelConstraintScope *constraint_scope() const {
		return m_constraint_scope_s.back();
	}

	IModelConstraintScope *pop_constraint_scope();

	uint32_t build_phase() const { return m_build_phase_s.back(); }

	void push_build_phase(uint32_t p);

	void pop_build_phase();

	obj *build_scope() const { return m_build_scope_s.back(); }

	template <class T> T *build_scopeT() const {
		return dynamic_cast<T *>(build_scope());
	}

	void push_build_scope(obj *s);

	void pop_build_scope();

	ModelField *build_field() const;

	void push_build_field(ModelField *f);

	void pop_build_field();

	DataTypeInt *type_int(
			bool		is_signed,
			int32_t		width);

	/**
	 * Derives a randstate from the master copy
	 */
	RandState *mk_randstate();

private:
	std::vector<IModelExprUP>					m_expr_s;
	std::vector<ctor_ctxt_up>					m_scope_s;
	std::vector<bool>							m_expr_mode;
	std::unordered_map<int32_t, DataTypeIntUP>	m_si_type_m;
	std::unordered_map<int32_t, DataTypeIntUP>	m_ui_type_m;
	std::vector<IModelConstraintScope *>		m_constraint_scope_s;
	std::vector<uint32_t>						m_build_phase_s;
	std::vector<obj *>							m_build_scope_s;
	std::vector<ModelField *>					m_build_field_s;
	RandState									m_randstate;
	static std::unique_ptr<ctor>				m_inst;

};

} /* namespace facade */
} /* namespace vsc */


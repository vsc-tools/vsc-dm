/*
 * ctor.h
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <vector>
#include "ctor_ctxt.h"

namespace vsc {

class ModelField;

namespace facade {

class rand_obj;

class ctor {
public:
	ctor();

	virtual ~ctor();

	static ctor *inst();

	static void reset();

	ModelField *model_scope();

	std::string scope_name();

	rand_obj *scope();

	void scope_ctor(
			const std::string			&name,
			rand_obj					*scope,
			const std::type_info		*ti);

	void scope_dtor(
			const std::string			&name,
			rand_obj					*scope,
			const std::type_info		*ti);

	void push_expr_mode(bool expr_mode=true);

	bool is_expr_mode() const;

	void pop_expr_mode();

private:
	std::vector<ctor_ctxt_up>			m_scope_s;
	std::vector<bool>					m_expr_mode;
	static std::unique_ptr<ctor>		m_inst;

};

} /* namespace facade */
} /* namespace vsc */


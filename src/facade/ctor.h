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
#include "ModelExpr.h"

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

private:
	std::vector<ModelExprUP>			m_expr_s;
	std::vector<ctor_ctxt_up>			m_scope_s;
	std::vector<bool>					m_expr_mode;
	static std::unique_ptr<ctor>		m_inst;

};

} /* namespace facade */
} /* namespace vsc */


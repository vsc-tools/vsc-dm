/*
 * ctor_ctxt.h
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include <vector>

namespace vsc {
namespace facade {

class rand_obj;

class ctor_ctxt;
using ctor_ctxt_up = std::unique_ptr<ctor_ctxt>;
class ctor_ctxt {
public:
	ctor_ctxt(
			const std::string		&name,
			rand_obj				*scope);

	virtual ~ctor_ctxt();

	const std::string &name() const { return m_name; }

	void name(const std::string &n) { m_name = n; }

	rand_obj *scope() const { return m_scope; }

	void scope(rand_obj *s) { m_scope = s; }

	bool is_scope() const { return m_is_scope; }

	void is_scope(bool s) { m_is_scope = s; }

	const std::type_info *ti() const;

	void push_ti(const std::type_info *t);

	void pop_ti();

private:
	std::string								m_name;
	bool									m_is_scope;
	rand_obj								*m_scope;
	std::vector<const std::type_info *>		m_ti_s;

};

} /* namespace facade */
} /* namespace vsc */


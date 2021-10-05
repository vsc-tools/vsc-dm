/*
 * ctor_ctxt.h
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>

namespace vsc {
namespace facade {

class rand_obj;

class ctor_ctxt;
using ctor_ctxt_up = std::unique_ptr<ctor_ctxt>;
class ctor_ctxt {
public:
	ctor_ctxt(
			const std::string		&name,
			rand_obj				*scope,
			const std::type_info	*ti);

	virtual ~ctor_ctxt();

	const std::string &name() const { return m_name; }

	void name(const std::string &n) { m_name = n; }

	rand_obj *scope() const { return m_scope; }

	void scope(rand_obj *s) { m_scope = s; }

	const std::type_info *ti() const { return m_ti; }

	void ti(const std::type_info *t) { m_ti = t; }

private:
	std::string					m_name;
	rand_obj					*m_scope;
	const std::type_info		*m_ti;

};

} /* namespace facade */
} /* namespace vsc */


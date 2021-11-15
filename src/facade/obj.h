/*
 * obj.h
 *
 *  Created on: Nov 14, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "obj_t.h"

namespace vsc {
namespace facade {

class obj_scope;

class obj {
	friend class ctor;
public:
	obj(obj_t t);

	virtual ~obj();

	bool is_type(obj_t flags) const { return (m_type & flags) == flags; }

	obj_t type() const { return m_type; }

	const std::string &name() const { return m_name; }

	void name(const std::string &n) { m_name = n; }

	std::string fullname() const;

	obj_scope *parent() const { return m_parent; }

	void parent(obj_scope *p) { m_parent = p; }

	virtual void build() = 0;

protected:

	obj_t				m_type;
	std::string			m_name;
	obj_scope			*m_parent;

};

} /* namespace facade */
} /* namespace vsc */


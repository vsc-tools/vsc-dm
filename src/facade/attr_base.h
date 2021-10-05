/*
 * attr_base.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "ModelFieldRoot.h"

namespace vsc {
namespace facade {

class attr_base {
public:
	attr_base();

	virtual ~attr_base();

	const std::string &name() const { return m_name; }

	void name(const std::string &n) { m_name = n; }

	std::string fullname() const;

	attr_base *parent() const { return m_parent; }

	void parent(attr_base *p) { m_parent = p; }

	ModelField *field() const { return m_field; }


protected:
	std::string					m_name;
	attr_base					*m_parent;

	ModelFieldRoot				*m_field;
	ModelFieldRootUP			m_field_u;

};

} /* namespace facade */
} /* namespace vsc */


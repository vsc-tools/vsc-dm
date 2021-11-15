/*
 * attr_scope.h
 *
 *  Created on: Nov 14, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "obj.h"

namespace vsc {
namespace facade {

class obj_scope : public obj {
public:
	obj_scope(obj_t t);

	virtual ~obj_scope();

	const std::vector<obj *> &children() const { return m_children; }

	void add_child(obj *c) { m_children.push_back(c); }

protected:

	virtual void build();

private:
	std::vector<obj *>				m_children;


};

} /* namespace facade */
} /* namespace vsc */


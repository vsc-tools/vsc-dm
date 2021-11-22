/*
 * obj.cpp
 *
 *  Created on: Nov 14, 2021
 *      Author: mballance
 */

#include "ctor.h"
#include "obj.h"
#include "obj_scope.h"
#include "Debug.h"

#undef EN_DEBUG_OBJ

#ifdef EN_DEBUG_OBJ
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(obj, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(obj, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(obj, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {
namespace facade {

obj::obj(obj_t t) : m_parent(0), m_type(t) {
	DEBUG_ENTER("obj");
	// TODO Auto-generated constructor stub

	m_name = ctor::inst()->scope_name();
	obj *s = ctor::inst()->scope(this);

	DEBUG("name=%s scope=%p", m_name.c_str(), s);

	// TOOD: assign a name for anonymous fields

	if (s && s->is_type(ObjType_Scope)) {
		m_parent = static_cast<obj_scope *>(s);
		m_parent->add_child(this);
	} else {
		m_parent = 0;
	}
	DEBUG_LEAVE("obj");
}

obj::~obj() {
	// TODO Auto-generated destructor stub
}

std::string obj::fullname() const {
	std::string ret = m_name;

	obj_scope *p = m_parent;
	while (p) {
		ret.insert(0, ".");
		ret.insert(0, p->m_name);
		p = p->m_parent;
	}

	return ret;
}

} /* namespace facade */
} /* namespace vsc */

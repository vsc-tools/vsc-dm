/*
 * ModelFieldRef.cpp
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#include "ModelFieldRef.h"

namespace vsc {

ModelFieldRef::ModelFieldRef() : m_parent(0),
		m_flags(ModelFieldFlag::NoFlags), m_ref(0) {

}

ModelFieldRef::~ModelFieldRef() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

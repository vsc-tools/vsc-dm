/*
 * TypeExprFieldRef.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#include "TypeExprFieldRef.h"

namespace vsc {
namespace dm {

TypeExprFieldRef::TypeExprFieldRef(
    ITypeExprFieldRef::RootRefKind      kind,
    int32_t                             offset) :
        m_root_ref_kind(kind), m_root_ref_offset(offset) {

}

TypeExprFieldRef::~TypeExprFieldRef() {
	// TODO Auto-generated destructor stub
}

void TypeExprFieldRef::addPathElem(int32_t idx) {
	m_path.push_back(idx);
}

}
} /* namespace vsc */


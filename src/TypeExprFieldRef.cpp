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
    int32_t                             offset,
    int32_t                             index) : 
        m_root_ref_kind(kind), m_root_ref_offset(offset),
        m_subfield_index(index) {
}

TypeExprFieldRef::~TypeExprFieldRef() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */


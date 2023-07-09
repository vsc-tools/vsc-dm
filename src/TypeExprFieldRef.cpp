/*
 * TypeExprFieldRef.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#include "TypeExprFieldRef.h"

namespace vsc {
namespace dm {

TypeExprFieldRef::TypeExprFieldRef(ITypeExpr *root) : 
    m_root_ref_kind(RootRefKind::RootExpr), m_root_expr(root) {

}

TypeExprFieldRef::TypeExprFieldRef(
    ITypeExprFieldRef::RootRefKind      kind,
    int32_t                             offset) : m_root_ref_kind(kind) {
    if (offset >= 0) {
        m_path.push_back(offset);
    }
}

TypeExprFieldRef::~TypeExprFieldRef() {
	// TODO Auto-generated destructor stub
}

void TypeExprFieldRef::addPathElem(int32_t idx) {
	m_path.push_back(idx);
}

}
} /* namespace vsc */


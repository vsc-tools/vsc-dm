/*
 * TypeExprFieldRef.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#include "TypeExprFieldRef.h"

namespace vsc {

TypeExprFieldRef::TypeExprFieldRef() {
	// TODO Auto-generated constructor stub

}

TypeExprFieldRef::~TypeExprFieldRef() {
	// TODO Auto-generated destructor stub
}

void TypeExprFieldRef::addIdxRef(int32_t idx) {
	m_path.push_back({TypeExprFieldRefElemKind::IdxOffset, idx});
}

void TypeExprFieldRef::addActiveScopeRef(int32_t off) {
	m_path.push_back({TypeExprFieldRefElemKind::ActiveScope, off});
}

void TypeExprFieldRef::addRootRef() {
	m_path.push_back({TypeExprFieldRefElemKind::Root, -1});
}

} /* namespace vsc */

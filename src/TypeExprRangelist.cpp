/*
 * TypeExprRangelist.cpp
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#include "TypeExprRangelist.h"

namespace vsc {
namespace dm {

TypeExprRangelist::TypeExprRangelist() {

}

TypeExprRangelist::~TypeExprRangelist() {
	// TODO Auto-generated destructor stub
}

void TypeExprRangelist::optimize() {

}

void TypeExprRangelist::addRange(ITypeExprRange *rng) {
	m_ranges.push_back(ITypeExprRangeUP(rng));
}

}
} /* namespace vsc */


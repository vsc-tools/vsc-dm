/*
 * ExprRangelist.cpp
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#include "ExprRangelist.h"

namespace vsc {

ExprRangelist::ExprRangelist() {
	// TODO Auto-generated constructor stub

}

ExprRangelist::~ExprRangelist() {
	// TODO Auto-generated destructor stub
}

void ExprRangelist::addRange(ExprRangeSP range) {
	m_ranges.push_back(range);
}

} /* namespace vsc */

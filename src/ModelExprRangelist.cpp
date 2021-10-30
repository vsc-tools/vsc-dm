/*
 * ModelExprRangelist.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#include "ModelExprRangelist.h"

namespace vsc {

ModelExprRangelist::ModelExprRangelist() {

}

ModelExprRangelist::ModelExprRangelist(
		const std::vector<ModelExprRange *> &ranges) {
	for (auto it=ranges.begin(); it!=ranges.end(); it++) {
		m_ranges.push_back(ModelExprRangeUP(*it));
	}
}

ModelExprRangelist::~ModelExprRangelist() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */

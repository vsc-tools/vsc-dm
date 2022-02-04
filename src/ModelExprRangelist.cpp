/*
 * ModelExprRangelist.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#include "ModelExprRangelist.h"

namespace vsc {

ModelExprRangelist::ModelExprRangelist() : m_width(-1) {

}

ModelExprRangelist::ModelExprRangelist(
		const std::vector<IModelExprRange *> &ranges) {
	m_width = -1;
	for (auto it=ranges.begin(); it!=ranges.end(); it++) {
		if ((*it)->width() > m_width) {
			m_width = (*it)->width();
		}
		m_ranges.push_back(IModelExprRangeUP(*it));
	}
}

ModelExprRangelist::~ModelExprRangelist() {
	// TODO Auto-generated destructor stub
}

void ModelExprRangelist::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprRangeList::eval\n");
}

} /* namespace vsc */

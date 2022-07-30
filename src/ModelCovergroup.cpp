/*
 * ModelCovergroup.cpp
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#include "ModelCovergroup.h"

namespace vsc {

ModelCovergroup::ModelCovergroup(const std::string &name) : ModelCoverItem(name) {
	// TODO Auto-generated constructor stub

}

ModelCovergroup::~ModelCovergroup() {
	// TODO Auto-generated destructor stub
}

void ModelCovergroup::finalize() {

}

void ModelCovergroup::sample() {
	for (auto it=m_coverpoints.begin(); it!=m_coverpoints.end(); it++) {
		(*it)->sample();
	}
	for (auto it=m_crosses.begin(); it!=m_crosses.end(); it++) {
		(*it)->sample();
	}
}

double ModelCovergroup::getCoverage() {
	return 0.0;
}

} /* namespace vsc */

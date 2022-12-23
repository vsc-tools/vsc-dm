/*
 * ModelCovergroup.cpp
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#include "ModelCovergroup.h"

namespace vsc {
namespace dm {

ModelCovergroup::ModelCovergroup(const std::string &name) : ModelCoverItem(name) {
	m_coverage = 0.0;
	m_coverage_valid = false;

}

ModelCovergroup::~ModelCovergroup() {
	// TODO Auto-generated destructor stub
}

void ModelCovergroup::addCoverpoint(IModelCoverpoint *cp) {
	cp->setCovergroup(this);
	m_coverpoints.push_back(IModelCoverpointUP(cp));
}

void ModelCovergroup::addCross(IModelCoverCross *cross) {
	cross->setCovergroup(this);
	m_crosses.push_back(IModelCoverCrossUP(cross));
}

void ModelCovergroup::finalize() {
	for (auto it=m_coverpoints.begin(); it!=m_coverpoints.end(); it++) {
		(*it)->finalize();
	}
	for (auto it=m_crosses.begin(); it!=m_crosses.end(); it++) {
		(*it)->finalize();
	}
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
	if (!m_coverage_valid) {
		uint32_t div = 0;
		m_coverage = 0.0;

		for (auto it=m_coverpoints.begin(); it!=m_coverpoints.end(); it++) {
			m_coverage += ((*it)->getCoverage() * (*it)->getOptions()->getWeight());
			div++;
		}
		for (auto it=m_crosses.begin(); it!=m_crosses.end(); it++) {
			m_coverage += ((*it)->getCoverage() * (*it)->getOptions()->getWeight());
			div++;
		}

		if (div) {
			m_coverage /= div;
		}
	}
	return m_coverage;
}

void ModelCovergroup::coverageEvent() {
	m_coverage_valid = false;
}

}
} /* namespace vsc */

/*
 * ModelCoverCross.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: mballance
 */

#include <string.h>
#include "ModelCoverCross.h"

namespace vsc {

ModelCoverCross::ModelCoverCross(
	const std::string			&name,
	IModelCoverpointIff			*iff) :
		ModelCoverItem(name), m_iff(iff), m_bins_val(0), 
		m_n_bins(-1), m_coverage_valid(false), m_coverage(0) {
	// TODO Auto-generated constructor stub

}

ModelCoverCross::~ModelCoverCross() {
	if (m_bins_val) {
		delete [] m_bins_val;
	}
}

void ModelCoverCross::finalize() {
	m_n_bins = 1;
	for (auto it=m_coverpoints.begin(); it!=m_coverpoints.end(); it++) {
		m_n_bins *= (*it)->getNumBins(ModelCoverBinType::Bins);
	}
	m_bins_val = new uint32_t[m_n_bins];
	memset(m_bins_val, 0, sizeof(uint32_t)*m_n_bins);
}

void ModelCoverCross::sample() {
	uint32_t bin_mult = 1;
	uint32_t bin_idx = 0;
	bool have_hit = true;

	bool iff = true;
	if (m_iff) {
		iff = m_iff->getIff();
	}

	if (iff) {

	// TODO:
	for (auto it=m_coverpoints.begin(); it!=m_coverpoints.end(); it++) {
		int32_t hit_idx = -1; // (*it)->hit_idx();
		if (hit_idx == -1) {
			have_hit = false;
			break;
		} else {
			bin_idx += (hit_idx*bin_mult);
			bin_mult *= (*it)->getNumBins(ModelCoverBinType::Bins);
		}
	}

	if (have_hit) {
		m_coverage_valid = false;
		m_bins_val[bin_idx]++;
	}
	} 
}

std::string ModelCoverCross::getBinName(int32_t bin_idx) {
	std::string ret;

	// TODO:
	return ret;
}

double ModelCoverCross::getCoverage() {
	uint32_t at_least = 1;
	if (!m_coverage_valid) {
		m_coverage = 0.0;
		for (uint32_t i=0; i<m_n_bins; i++) {
			if (m_bins_val[i] >= at_least) {
				m_coverage += 1;
			}
		}
		m_coverage *= 100;
		m_coverage /= m_n_bins;
		m_coverage_valid = true;
	}
	return m_coverage;
}

} /* namespace vsc */

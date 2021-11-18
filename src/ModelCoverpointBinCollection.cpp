/*
 * ModelCoverpointBinCollection.cpp
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#include "ModelCoverpointBinCollection.h"

namespace vsc {

ModelCoverpointBinCollection::ModelCoverpointBinCollection() {
	// TODO Auto-generated constructor stub

}

ModelCoverpointBinCollection::~ModelCoverpointBinCollection() {
	// TODO Auto-generated destructor stub
}

int32_t ModelCoverpointBinCollection::finalize(
			ModelCoverpoint			*cp,
			int32_t					bin_idx_base) {
	m_n_bins = 0;
	m_bin_idx_base = bin_idx_base;

	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		m_n_bins += (*it)->finalize(cp, bin_idx_base+m_n_bins);
	}

	return m_n_bins;
}

std::string ModelCoverpointBinCollection::bin_name(int32_t bin_idx) {
	IModelCoverpointBins *b = 0;

	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		if ((*it)->n_bins() > bin_idx) {
			b = it->get();
			break;
		} else {
			bin_idx -= (*it)->n_bins();
		}
	}

	return b->bin_name(bin_idx);
}

void ModelCoverpointBinCollection::sample() {
	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		(*it)->sample();
	}
}

} /* namespace vsc */

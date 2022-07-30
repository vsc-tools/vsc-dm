/*
 * ModelCoverBinCollection.cpp
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#include "ModelCoverBinCollection.h"

namespace vsc {

ModelCoverBinCollection::ModelCoverBinCollection(ModelCoverBinType type) : 
	ModelCoverBin("", type, false) {
	// TODO Auto-generated constructor stub

}

ModelCoverBinCollection::~ModelCoverBinCollection() {
	// TODO Auto-generated destructor stub
}

int32_t ModelCoverBinCollection::finalize(int32_t bin_idx_base) {
	m_n_bins = 0;
	m_bin_idx_base = bin_idx_base;

	for (std::vector<IModelCoverBinUP>::const_iterator
		it=m_bins.begin(); it!=m_bins.end(); it++) {
		m_n_bins += (*it)->finalize(bin_idx_base+m_n_bins);
	}

	return m_n_bins;
}

std::string ModelCoverBinCollection::getBinName(int32_t bin_idx) {
	IModelCoverBin *b = 0;

	for (std::vector<IModelCoverBinUP>::const_iterator
			it=m_bins.begin(); it!=m_bins.end(); it++) {
		if ((*it)->getNumBins() > bin_idx) {
			b = it->get();
			break;
		} else {
			bin_idx -= (*it)->getNumBins();
		}
	}

	return b->getBinName(bin_idx);
}

void ModelCoverBinCollection::sample() {
	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		(*it)->sample();
	}
}

} /* namespace vsc */

/*
 * ModelCoverpoint.cpp
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#include "vsc/dm/IModelCovergroup.h"
#include "ModelCoverpoint.h"
#include <string.h>

namespace vsc {
namespace dm {

ModelCoverpoint::ModelCoverpoint(
		const std::string		&name,
		IModelCoverpointTarget	*target,
		IModelCoverpointIff		*iff) : 
		ModelCoverItem(name), m_target(target), m_iff(iff),
		m_n_bins(-1), m_n_ignore_bins(-1), m_n_illegal_bins(-1),
		m_bins_val(0), m_ignore_bins_val(0), m_illegal_bins_val(0) {
	m_coverage_valid = false;
	m_coverage = 0.0;
	m_val.setBits(32); // TODO: needs to be passed in
}

ModelCoverpoint::~ModelCoverpoint() {
	if (m_bins_val) {
		delete [] m_bins_val;
	}
	if (m_ignore_bins_val) {
		delete [] m_ignore_bins_val;
	}
	if (m_illegal_bins_val) {
		delete [] m_illegal_bins_val;
	}
}

void ModelCoverpoint::addBin(IModelCoverBin *bin) {
	bin->setCoverpoint(this);
	switch (bin->getType()) {
	case ModelCoverBinType::Bins:
		m_bins.push_back(IModelCoverBinUP(bin));
		break;
	case ModelCoverBinType::IgnoreBins:
		m_ignore_bins.push_back(IModelCoverBinUP(bin));
		break;
	case ModelCoverBinType::IllegalBins:
		m_illegal_bins.push_back(IModelCoverBinUP(bin));
		break;
	}
}

void ModelCoverpoint::finalize() {
	uint32_t n_bins = 0;

	n_bins = 0;
	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		n_bins += (*it)->finalize(n_bins);
	}
	m_n_bins = n_bins;

	if (!n_bins) {
		n_bins = 1;
	}

	m_bins_val = new uint32_t[n_bins];
	memset(m_bins_val, 0, sizeof(uint32_t)*n_bins);

	n_bins = 0;
	for (auto it=m_ignore_bins.begin(); it!=m_ignore_bins.end(); it++) {
		n_bins += (*it)->finalize(n_bins);
	}
	m_n_ignore_bins = n_bins;

	if (!n_bins) {
		n_bins = 1;
	}

	m_ignore_bins_val = new uint32_t[n_bins];
	memset(m_ignore_bins_val, 0, sizeof(uint32_t)*n_bins);

	n_bins = 0;
	for (auto it=m_illegal_bins.begin(); it!=m_illegal_bins.end(); it++) {
		n_bins += (*it)->finalize(n_bins);
	}
	m_n_illegal_bins = n_bins;

	if (!n_bins) {
		n_bins = 1;
	}

	m_illegal_bins_val = new uint32_t[n_bins];
	memset(m_illegal_bins_val, 0, sizeof(uint32_t)*n_bins);
}

void ModelCoverpoint::sample() {
	m_bins_hit_idx.clear();
	m_ignore_hit_idx.clear();
	m_illegal_hit_idx.clear();

	// In the case of a type coverage, we trust that
	// someone will provide a value
	if (m_target) {
		m_target->getValue(&m_val);
	}

	bool iff = true;
	
	if (m_iff) {
		iff = m_iff->getIff();
	}

	if (iff) {
		for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
			(*it)->sample();
		}
	}
}

const std::vector<int32_t> &ModelCoverpoint::getHitIdx(ModelCoverBinType type) {
	switch (type) {
		case ModelCoverBinType::Bins: return m_bins_hit_idx;
		case ModelCoverBinType::IgnoreBins: return m_ignore_hit_idx;
		case ModelCoverBinType::IllegalBins: return m_illegal_hit_idx;
	}
	return m_bins_hit_idx;
}

std::string ModelCoverpoint::getBinName(ModelCoverBinType type, int32_t bin_idx) {
	IModelCoverBin *b = 0;

	switch (type) {
	case ModelCoverBinType::Bins: {
		for (std::vector<IModelCoverBinUP>::const_iterator 
			it=m_bins.begin(); it!=m_bins.end(); it++) {
			if (bin_idx < (*it)->getNumBins()) {
				b = it->get();
				break;
			}
		}
	} break;
	}

	if (b) {
		return b->getBinName(bin_idx);
	} else {
		return "<unknown>";
	}
}

int32_t ModelCoverpoint::getBinHits(ModelCoverBinType type, int32_t bin_idx) {
	IModelCoverBin *b = 0;

	switch (type) {
	case ModelCoverBinType::Bins: {
		for (std::vector<IModelCoverBinUP>::const_iterator 
			it=m_bins.begin(); it!=m_bins.end(); it++) {
			if (bin_idx < (*it)->getNumBins()) {
				b = it->get();
				break;
			}
		}
	} break;
	}

	if (b) {
		return b->getBinHits(bin_idx);
	} else {
		return -1;
	}
}

const IModelVal *ModelCoverpoint::getVal() {
	return &m_val;
}

void ModelCoverpoint::setVal(const IModelVal *v) {
	m_val.set(v);
}

void ModelCoverpoint::coverageEvent(ModelCoverBinType type, int32_t index) {
	uint32_t at_least = 1;

	switch (type) {
	case ModelCoverBinType::Bins: {
		uint32_t old_hit_val = m_bins_val[index];
		uint32_t new_hit_val;
		m_bins_hit_idx.push_back(index);
		m_coverage_valid = false;
		new_hit_val = (++m_bins_val[index]);

		if (old_hit_val < at_least && new_hit_val > at_least) {
			m_cg->coverageEvent();
		}
	} break;
	case ModelCoverBinType::IgnoreBins:
		m_ignore_hit_idx.push_back(index);
		m_ignore_bins_val[index]++;
		break;
	case ModelCoverBinType::IllegalBins:
		m_illegal_hit_idx.push_back(index);
		m_illegal_bins_val[index]++;
		break;
	}
}

double ModelCoverpoint::getCoverage() {
	if (!m_coverage_valid) {
		m_coverage = 0.0;
		uint32_t at_least = 1;

		for (uint32_t bi=0; bi<m_n_bins; bi++) {
			if (m_bins_val[bi] >= at_least) {
				m_coverage += 1;
			}
		}

		m_coverage *= 100;
		m_coverage /= m_n_bins;
		m_coverage_valid = true;
	}

	return m_coverage;
}

}
} /* namespace vsc */

/*
 * ModelCoverpoint.cpp
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#include "ModelCoverpoint.h"
#include <string.h>

namespace vsc {

ModelCoverpoint::ModelCoverpoint(
		ModelExpr			*target,
		const std::string	&name,
		ModelExpr			*iff) : m_target(target), m_name(name), m_iff(iff) {
	m_hit_idx = -1;
	m_n_bins = -1;
	m_bins_val = 0;
	m_n_ignore_bins = -1;
	m_ignore_bins_val = 0;
	m_n_illegal_bins = -1;
	m_illegal_bins_val = 0;
	m_coverage_valid = false;
	m_coverage = 0.0;

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

void ModelCoverpoint::add_bins(IModelCoverpointBins *bins) {
	switch (bins->bin_type()) {
	case BinsType::Bins:
		m_bins.push_back(IModelCoverpointBinsUP(bins));
		break;
	case BinsType::IgnoreBins:
		m_ignore_bins.push_back(IModelCoverpointBinsUP(bins));
		break;
	case BinsType::IllegalBins:
		m_illegal_bins.push_back(IModelCoverpointBinsUP(bins));
		break;
	}
}

void ModelCoverpoint::finalize() {
	uint32_t n_bins;

	n_bins = 0;
	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		n_bins += (*it)->finalize(this, n_bins);
	}
	m_n_bins = n_bins;

	if (!n_bins) {
		n_bins = 1;
	}

	m_bins_val = new uint32_t[n_bins];
	memset(m_bins_val, 0, sizeof(uint32_t)*n_bins);

	n_bins = 0;
	for (auto it=m_ignore_bins.begin(); it!=m_ignore_bins.end(); it++) {
		n_bins += (*it)->finalize(this, n_bins);
	}
	m_n_ignore_bins = n_bins;

	if (!n_bins) {
		n_bins = 1;
	}

	m_ignore_bins_val = new uint32_t[n_bins];
	memset(m_ignore_bins_val, 0, sizeof(uint32_t)*n_bins);

	n_bins = 0;
	for (auto it=m_illegal_bins.begin(); it!=m_illegal_bins.end(); it++) {
		n_bins += (*it)->finalize(this, n_bins);
	}
	m_n_illegal_bins = n_bins;

	if (!n_bins) {
		n_bins = 1;
	}

	m_illegal_bins_val = new uint32_t[n_bins];
	memset(m_illegal_bins_val, 0, sizeof(uint32_t)*n_bins);
}

void ModelCoverpoint::sample() {
	m_hit_idx = -1;

	// TODO: evaluate expression

	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		(*it)->sample();
	}
}

std::string ModelCoverpoint::bin_name(int32_t bin_idx) {
	IModelCoverpointBins *b = 0;
	for (auto it=m_bins.begin(); it!=m_bins.end(); it++) {
		if (bin_idx < (*it)->n_bins()) {
			b = it->get();
			break;
		}
	}
	return b->bin_name(bin_idx);
}

std::string ModelCoverpoint::ignore_bin_name(int32_t bin_idx) {
	IModelCoverpointBins *b = 0;
	for (auto it=m_ignore_bins.begin(); it!=m_ignore_bins.end(); it++) {
		if (bin_idx < (*it)->n_bins()) {
			b = it->get();
			break;
		}
	}
	return b->bin_name(bin_idx);
}

std::string ModelCoverpoint::illegal_bin_name(int32_t bin_idx) {
	IModelCoverpointBins *b = 0;
	for (auto it=m_illegal_bins.begin(); it!=m_illegal_bins.end(); it++) {
		if (bin_idx < (*it)->n_bins()) {
			b = it->get();
			break;
		}
	}
	return b->bin_name(bin_idx);
}

void ModelCoverpoint::coverage_ev(int32_t bin, BinsType type) {
	m_hit_idx = bin;
	switch (type) {
	case BinsType::Bins:
		m_coverage_valid = false;
		m_bins_val[bin]++;
		m_hit_idx = bin;
		break;
	case BinsType::IgnoreBins:
		m_ignore_bins_val[bin]++;
		break;
	case BinsType::IllegalBins:
		m_illegal_bins_val[bin]++;
		break;
	}
}

double ModelCoverpoint::coverage() {
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

} /* namespace vsc */

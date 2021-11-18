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
	m_bins_val = 0;
	m_ignore_bins_val = 0;
	m_illegal_bins_val = 0;
	// TODO Auto-generated constructor stub

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

	if (!n_bins) {
		n_bins = 1;
	}

	m_bins_val = new uint32_t[n_bins];
	memset(m_bins_val, 0, sizeof(uint32_t)*n_bins);

	n_bins = 0;
	for (auto it=m_ignore_bins.begin(); it!=m_ignore_bins.end(); it++) {
		n_bins += (*it)->finalize(this, n_bins);
	}

	if (!n_bins) {
		n_bins = 1;
	}

	m_ignore_bins_val = new uint32_t[n_bins];
	memset(m_ignore_bins_val, 0, sizeof(uint32_t)*n_bins);

	n_bins = 0;
	for (auto it=m_illegal_bins.begin(); it!=m_illegal_bins.end(); it++) {
		n_bins += (*it)->finalize(this, n_bins);
	}

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

void ModelCoverpoint::coverage_ev(int32_t bin, BinsType type) {
	m_hit_idx = bin;
	switch (type) {
	case BinsType::Bins:
		m_bins_val[bin]++;
		break;
	case BinsType::IgnoreBins:
		m_ignore_bins_val[bin]++;
		break;
	case BinsType::IllegalBins:
		m_illegal_bins_val[bin]++;
		break;
	}
}

} /* namespace vsc */

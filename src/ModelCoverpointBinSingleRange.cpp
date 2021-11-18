/*
 * ModelCoverpointBinSingleRange.cpp
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#include "ModelCoverpointBinSingleRange.h"

namespace vsc {

ModelCoverpointBinSingleRange::ModelCoverpointBinSingleRange(
		const std::string			&name,
		const ModelVal				&lower,
		const ModelVal				&upper) : m_name(name),
				m_lower(lower), m_upper(upper) {

}

ModelCoverpointBinSingleRange::~ModelCoverpointBinSingleRange() {
	// TODO Auto-generated destructor stub
}

int32_t ModelCoverpointBinSingleRange::finalize(
		ModelCoverpoint			*cp,
		int32_t					bin_idx_base) {
	m_n_bins = 1;
	m_cp = cp;
	m_bin_idx_base = bin_idx_base;

	return m_n_bins;
}

std::string ModelCoverpointBinSingleRange::bin_name(int32_t bin_idx) {
	return m_name;
}

void ModelCoverpointBinSingleRange::sample() {
	// TODO:
}

} /* namespace vsc */

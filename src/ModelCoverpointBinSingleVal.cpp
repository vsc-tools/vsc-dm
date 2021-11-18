/*
 * ModelCoverpointBinSingleVal.cpp
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#include "ModelCoverpointBinSingleVal.h"

namespace vsc {

ModelCoverpointBinSingleVal::ModelCoverpointBinSingleVal(
		const std::string			&name,
		const ModelVal				&val) : m_name(name), m_val(val) {
}

ModelCoverpointBinSingleVal::~ModelCoverpointBinSingleVal() {
	// TODO Auto-generated destructor stub
}

int32_t ModelCoverpointBinSingleVal::finalize(
		ModelCoverpoint			*cp,
		int32_t					bin_idx_base) {
	m_cp = cp;
	m_bin_idx_base = bin_idx_base;
	m_n_bins = 1;

	return m_n_bins;
}

std::string ModelCoverpointBinSingleVal::bin_name(int32_t bin_idx) {
	return m_name;
}

void ModelCoverpointBinSingleVal::sample() {
	// TODO:
}

} /* namespace vsc */

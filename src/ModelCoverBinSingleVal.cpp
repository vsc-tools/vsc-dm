/*
 * ModelCoverBinSingleVal.cpp
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#include "ModelCoverpoint.h"
#include "ModelCoverBinSingleVal.h"
#include "ModelValOp.h"

namespace vsc {

ModelCoverBinSingleVal::ModelCoverBinSingleVal(
		const std::string			&name,
		ModelCoverBinType			type,
		const IModelVal				*val) : 
			ModelCoverBin(name, type, false), m_val(val) {
	m_count = 0;
}

ModelCoverBinSingleVal::~ModelCoverBinSingleVal() {
	// TODO Auto-generated destructor stub
}

int32_t ModelCoverBinSingleVal::finalize(int32_t bin_idx_base) {
	m_bin_idx_base = bin_idx_base;
	m_n_bins = 1;

	return m_n_bins;
}

std::string ModelCoverBinSingleVal::getBinName(int32_t bin_idx) {
	return m_name;
}

int32_t ModelCoverBinSingleVal::getBinHits(int32_t bin_idx) {
	return m_count;
}

void ModelCoverBinSingleVal::sample() {
	fprintf(stdout, "getVal: %lld m_val=%lld\n", 
		m_cp->getVal()->val_u(),
		m_val.val_u());
	if (ModelValOp::eq_s(&m_val, m_cp->getVal())) {
		// Notify the coverpoint...
		m_count++;
		m_cp->coverageEvent(m_type, m_bin_idx_base);
	}
}

} /* namespace vsc */

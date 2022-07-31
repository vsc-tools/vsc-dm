/*
 * ModelCoverBinSingleRange.cpp
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#include "ModelCoverpoint.h"
#include "ModelCoverBinSingleRange.h"
#include "ModelValOp.h"

namespace vsc {

ModelCoverBinSingleRange::ModelCoverBinSingleRange(
		const std::string			&name,
		ModelCoverBinType			type,
		bool						is_signed,
		const IModelVal				*lower,
		const IModelVal				*upper) : 
			ModelCoverBin(name, type, is_signed),
			m_lower(lower), m_upper(upper) {
	m_count = 0;
}

ModelCoverBinSingleRange::~ModelCoverBinSingleRange() {
	// TODO Auto-generated destructor stub
}

int32_t ModelCoverBinSingleRange::finalize(int32_t bin_idx_base) {
	m_n_bins = 1;
	m_bin_idx_base = bin_idx_base;

	return m_n_bins;
}

std::string ModelCoverBinSingleRange::getBinName(int32_t bin_idx) {
	return m_name;
}

void ModelCoverBinSingleRange::sample() {
	if (m_is_signed) {
		if (ModelValOp::sge_s(m_cp->getVal(), &m_lower) && 
				ModelValOp::sle_s(m_cp->getVal(), &m_upper)) {
			m_count++;
			m_cp->coverageEvent(m_type, m_bin_idx_base);
		}
	} else {
		if (ModelValOp::uge_s(m_cp->getVal(), &m_lower) && 
				ModelValOp::ule_s(m_cp->getVal(), &m_upper)) {
			m_count++;
			m_cp->coverageEvent(m_type, m_bin_idx_base);
		}
	}
}

} /* namespace vsc */

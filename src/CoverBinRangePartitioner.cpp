/*
 * CoverBinRangePartitioner.cpp
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#include "CoverBinRangePartitioner.h"

namespace vsc {

CoverBinRangePartitioner::CoverBinRangePartitioner() : m_specs(0) {
	// TODO Auto-generated constructor stub

}

CoverBinRangePartitioner::~CoverBinRangePartitioner() {
	// TODO Auto-generated destructor stub
}

void CoverBinRangePartitioner::partition(
		std::vector<CoverBinSpecUP>		&specs,
		const ModelValRangelist			&ranges,
		int32_t							auto_bin_max) {

	// Determine how many values we're actually dealing with
	uint64_t n_values = 0;
	for (auto it=ranges.begin(); it!=ranges.end(); it++) {
		if (ranges.is_signed()) {
			n_values += (it->upper().val_i()-it->lower().val_i()+1);
		} else {
			n_values += (it->upper().val_u()-it->lower().val_u()+1);
		}
	}

}

} /* namespace vsc */

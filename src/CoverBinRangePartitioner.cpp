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
	for (uint32_t i=0; i<ranges.size(); i++) {
		const IModelValRange *rng = ranges.at(i);

		if (ranges.getIsSigned()) {
			n_values += (rng->upper()->val_i()-rng->lower()->val_i()+1);
		} else {
			n_values += (rng->upper()->val_u()-rng->lower()->val_u()+1);
		}
	}
}

} /* namespace vsc */

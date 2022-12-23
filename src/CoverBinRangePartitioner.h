/*
 * CoverBinRangePartitioner.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */
#pragma once
#include <vector>
#include "CoverBinSpec.h"
#include "ModelValRangelist.h"

namespace vsc {
namespace dm {

class CoverBinRangePartitioner {
public:
	CoverBinRangePartitioner();

	virtual ~CoverBinRangePartitioner();

	void partition(
			std::vector<CoverBinSpecUP>		&specs,
			const ModelValRangelist 		&ranges,
			int32_t							auto_bin_max);

private:
	std::vector<CoverBinSpecUP>				*m_specs;

};

}
} /* namespace vsc */

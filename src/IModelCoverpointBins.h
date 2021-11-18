/*
 * IModelCoverpointBins.h
 *
 *  Created on: Nov 16, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include <string>
#include "BinsType.h"
#include "IAccept.h"

namespace vsc {

class ModelCoverpoint;

class IModelCoverpointBins;
using IModelCoverpointBinsUP=std::unique_ptr<IModelCoverpointBins>;
class IModelCoverpointBins : public IAccept {
public:

	virtual int32_t finalize(
			ModelCoverpoint			*cp,
			int32_t					bin_idx_base) = 0;

	virtual std::string bin_name(int32_t bin_idx) = 0;

	virtual void sample() = 0;

	virtual int32_t n_bins() = 0;

	virtual BinsType bin_type() = 0;

	virtual void bin_type(BinsType t) = 0;
};

}

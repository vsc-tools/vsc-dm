/*
 * ModelCoverpointBinCollection.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ModelCoverpointBinsBase.h"

namespace vsc {

class ModelCoverpointBinCollection : public ModelCoverpointBinsBase {
public:
	ModelCoverpointBinCollection();

	virtual ~ModelCoverpointBinCollection();

	virtual int32_t finalize(
			ModelCoverpoint			*cp,
			int32_t					bin_idx_base) override;

	virtual std::string bin_name(int32_t bin_idx) override;

	virtual void sample() override;

	void add_bin(IModelCoverpointBins *b) {
		m_bins.push_back(IModelCoverpointBinsUP(b));
	}

private:
	std::vector<IModelCoverpointBinsUP>		m_bins;
};

} /* namespace vsc */


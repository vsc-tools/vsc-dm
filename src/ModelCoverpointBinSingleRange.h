/*
 * ModelCoverpointBinSingleRange.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelCoverpointBinsBase.h"
#include "ModelVal.h"

namespace vsc {

class ModelCoverpointBinSingleRange : public ModelCoverpointBinsBase {
public:
	ModelCoverpointBinSingleRange(
			const std::string			&name,
			const ModelVal				&lower,
			const ModelVal				&upper);

	virtual ~ModelCoverpointBinSingleRange();

	virtual int32_t finalize(
			ModelCoverpoint			*cp,
			int32_t					bin_idx_base) override;

	virtual std::string bin_name(int32_t bin_idx) override;

	virtual void sample() override;

private:
	std::string						m_name;
	ModelVal						m_lower;
	ModelVal						m_upper;
};

} /* namespace vsc */


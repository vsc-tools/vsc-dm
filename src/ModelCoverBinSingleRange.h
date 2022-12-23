/*
 * ModelCoverpointBinSingleRange.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelCoverBinSingleRange.h"
#include "ModelCoverBin.h"
#include "ModelVal.h"

namespace vsc {
namespace dm {

class ModelCoverBinSingleRange : 
	public virtual IModelCoverBinSingleRange, 
	public virtual ModelCoverBin {
public:
	ModelCoverBinSingleRange(
			const std::string			&name,
			ModelCoverBinType			type,
			bool						is_signed,
			const IModelVal				*lower,
			const IModelVal				*upper);

	virtual ~ModelCoverBinSingleRange();

	virtual int32_t finalize(int32_t bin_idx_base) override;

	virtual std::string getBinName(int32_t bin_idx) override;

	virtual int32_t getBinHits(int32_t bin_idx) override {
		return m_count;
	}

	virtual void sample() override;

	virtual void accept(IVisitor *v) override { v->visitModelCoverBinSingleRange(this); }

private:
	std::string						m_name;
	int32_t							m_count;
	ModelVal						m_lower;
	ModelVal						m_upper;
};

}
} /* namespace vsc */


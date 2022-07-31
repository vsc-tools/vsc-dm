/*
 * ModelCoverBinSingleVal.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelCoverBinSingleVal.h"
#include "ModelCoverBin.h"
#include "ModelVal.h"

namespace vsc {

class ModelCoverBinSingleVal : 
	public virtual IModelCoverBinSingleVal,
	public virtual ModelCoverBin {
public:
	ModelCoverBinSingleVal(
			const std::string			&name,
			ModelCoverBinType			type,
			const IModelVal				*val);

	virtual ~ModelCoverBinSingleVal();

	virtual int32_t finalize(int32_t bin_idx_base) override;

	virtual std::string getBinName(int32_t bin_idx) override;

    virtual int32_t getBinHits(int32_t bin_idx) override;

	virtual void sample() override;

	virtual void accept(IVisitor *v) override { v->visitModelCoverBinSingleVal(this); }

private:
	int32_t							m_count;
	std::string						m_name;
	ModelVal						m_val;
};

} /* namespace vsc */


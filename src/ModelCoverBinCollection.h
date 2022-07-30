/*
 * ModelCoverBinCollection.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IModelCoverBinCollection.h"
#include "ModelCoverBin.h"

namespace vsc {

class ModelCoverBinCollection : 
	public virtual IModelCoverBinCollection, 
	public virtual ModelCoverBin {
public:
	ModelCoverBinCollection(ModelCoverBinType type);

	virtual ~ModelCoverBinCollection();

	virtual int32_t finalize(int32_t bin_idx_base) override;

	virtual std::string getBinName(int32_t bin_idx) override;

	virtual void sample() override;

	virtual void addBin(IModelCoverBin *b) override {
		m_bins.push_back(IModelCoverBinUP(b));
	}

	virtual void accept(IVisitor *v) override { v->visitModelCoverBinCollection(this); }

private:
	std::vector<IModelCoverBinUP>		m_bins;
};

} /* namespace vsc */


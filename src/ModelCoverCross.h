/*
 * ModelCoverCross.h
 *
 *  Created on: Nov 16, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IAccept.h"
#include "vsc/IModelCoverCross.h"
#include "ModelCoverItem.h"

namespace vsc {

class ModelCoverCross;
using ModelCoverCrossUP=std::unique_ptr<ModelCoverCross>;
class ModelCoverCross : 
	public virtual IModelCoverCross, 
	public virtual ModelCoverItem {
public:
	ModelCoverCross(
		const std::string			&name,
		IModelCoverpointIff			*iff);

	virtual ~ModelCoverCross();

	virtual void setCovergroup(IModelCovergroup *cg) override { m_cg = cg; }

	virtual IModelCovergroup *getCovergroup() const { return m_cg; }

	virtual const std::vector<IModelCoverpoint *> &coverpoints() const override {
		return m_coverpoints;
	}

	virtual void addCoverpoint(IModelCoverpoint *cp) override {
		m_coverpoints.push_back(cp);
	}

	virtual void finalize() override;

	virtual void sample() override;

	virtual uint32_t getNumBins() const override { return m_n_bins; }

	virtual std::string getBinName(int32_t bin_idx) override;

	virtual int32_t getBinHits(int32_t bin_idx) override;

	virtual double getCoverage() override;

	virtual void accept(IVisitor *v) override { v->visitModelCoverCross(this); }

private:
	IModelCovergroup						*m_cg;
	IModelCoverpointIffUP					m_iff;
	std::vector<IModelCoverpoint *>			m_coverpoints;
	uint32_t								*m_bins_val;
	int32_t									m_n_bins;
	bool									m_coverage_valid;
	double									m_coverage;
};

} /* namespace vsc */


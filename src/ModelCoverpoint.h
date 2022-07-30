/*
 * ModelCoverpoint.h
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IModelCoverpoint.h"
#include "vsc/IModelCoverBin.h"
#include "ModelCoverItem.h"
#include "ModelCoverOpts.h"
#include "ModelExpr.h"
#include "ModelVal.h"

namespace vsc {

class ModelCoverpoint;
using ModelCoverpointUP=std::unique_ptr<ModelCoverpoint>;
class ModelCoverpoint : 
	public virtual IModelCoverpoint, 
	public virtual ModelCoverItem {
public:
	ModelCoverpoint(
			const std::string		&name,
			IModelCoverpointTarget	*target,
			IModelCoverpointIff		*iff);

	virtual ~ModelCoverpoint();

	virtual IModelCoverpointTarget *getTarget() const override { return m_target.get(); }

	virtual IModelCoverpointIff *getIff() const override { return m_iff.get(); }

	void addBin(IModelCoverBin *bin) override;

	virtual void finalize();

	virtual void sample();

	virtual const std::vector<int32_t> &getHitIdx(ModelCoverBinType type) override;

	virtual uint32_t getNumBins(ModelCoverBinType type) const override { return m_n_bins; }

	virtual std::string getBinName(ModelCoverBinType type, int32_t bin_idx) override;

	virtual void coverageEvent(ModelCoverBinType type, int32_t index) override;

	const IModelVal *getVal();

	void setVal(const IModelVal *v);

	double getCoverage();

	virtual void accept(IVisitor *v) override { v->visitModelCoverpoint(this); }

private:
	IModelCoverpointTargetUP				m_target;
	IModelCoverpointIffUP					m_iff;

	std::vector<int32_t>					m_bins_hit_idx;
	std::vector<int32_t>					m_ignore_hit_idx;
	std::vector<int32_t>					m_illegal_hit_idx;

	ModelVal								m_val;

	std::vector<IModelCoverBinUP>			m_bins;
	int32_t									m_n_bins;
	std::vector<IModelCoverBinUP>			m_ignore_bins;
	int32_t									m_n_ignore_bins;
	std::vector<IModelCoverBinUP>			m_illegal_bins;
	int32_t									m_n_illegal_bins;
	uint32_t								*m_bins_val;
	uint32_t								*m_ignore_bins_val;
	uint32_t								*m_illegal_bins_val;
	bool									m_coverage_valid;
	double									m_coverage;

};

} /* namespace vsc */


/*
 * ModelCoverpoint.h
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "IAccept.h"
#include "IModelCoverpointBins.h"
#include "ModelExpr.h"
#include "ModelVal.h"

namespace vsc {

class ModelCoverpoint;
using ModelCoverpointUP=std::unique_ptr<ModelCoverpoint>;
class ModelCoverpoint : public IAccept {
public:
	ModelCoverpoint(
			ModelExpr			*target,
			const std::string	&name,
			ModelExpr			*iff);

	virtual ~ModelCoverpoint();

	ModelExpr *target() const { return m_target.get(); }

	const std::string &name() const { return m_name; }

	ModelExpr *iff() const { return m_iff.get(); }

	void add_bins(IModelCoverpointBins *bins);

	virtual void finalize();

	virtual void sample();

	virtual void coverage_ev(int32_t bin, BinsType type);

	const ModelVal &val() const { return m_val; }

	void val(const ModelVal &v) { m_val = v; }

private:
	ModelExprUP								m_target;
	std::string								m_name;
	ModelExprUP								m_iff;

	int32_t									m_hit_idx;

	ModelVal								m_val;

	std::vector<IModelCoverpointBinsUP>		m_bins;
	std::vector<IModelCoverpointBinsUP>		m_ignore_bins;
	std::vector<IModelCoverpointBinsUP>		m_illegal_bins;
	uint32_t								*m_bins_val;
	uint32_t								*m_ignore_bins_val;
	uint32_t								*m_illegal_bins_val;

};

} /* namespace vsc */


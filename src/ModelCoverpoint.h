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

	int32_t hit_idx() const { return m_hit_idx; }

	int32_t n_bins() const { return m_n_bins; }

	std::string bin_name(int32_t bin_idx);

	int32_t n_ignore_bins() const { return m_n_ignore_bins; }

	std::string ignore_bin_name(int32_t bin_idx);

	int32_t n_illegal_bins() const { return m_n_illegal_bins; }

	std::string illegal_bin_name(int32_t bin_idx);

	virtual void coverage_ev(int32_t bin, BinsType type);

	const ModelVal &val() const { return m_val; }

	void val(const ModelVal &v) { m_val = v; }

	double coverage();

private:
	ModelExprUP								m_target;
	std::string								m_name;
	ModelExprUP								m_iff;

	int32_t									m_hit_idx;

	ModelVal								m_val;

	std::vector<IModelCoverpointBinsUP>		m_bins;
	int32_t									m_n_bins;
	std::vector<IModelCoverpointBinsUP>		m_ignore_bins;
	int32_t									m_n_ignore_bins;
	std::vector<IModelCoverpointBinsUP>		m_illegal_bins;
	int32_t									m_n_illegal_bins;
	uint32_t								*m_bins_val;
	uint32_t								*m_ignore_bins_val;
	uint32_t								*m_illegal_bins_val;
	bool									m_coverage_valid;
	double									m_coverage;

};

} /* namespace vsc */


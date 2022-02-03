/*
 * ModelCoverCross.h
 *
 *  Created on: Nov 16, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IAccept.h"
#include "ModelCoverpoint.h"

namespace vsc {

class ModelCoverCross;
using ModelCoverCrossUP=std::unique_ptr<ModelCoverCross>;
class ModelCoverCross : public IAccept {
public:
	ModelCoverCross();

	virtual ~ModelCoverCross();

	const std::vector<ModelCoverpoint *> &coverpoints() const {
		return m_coverpoints;
	}

	void add_coverpoint(ModelCoverpoint *cp) {
		m_coverpoints.push_back(cp);
	}

	void finalize();

	void sample();

	uint32_t n_bins() const { return m_n_bins; }

	std::string bin_name(int32_t bin_idx);

	double coverage();

	virtual void accept(IVisitor *v) override { v->visitModelCoverCross(this); }

private:
	std::vector<ModelCoverpoint *>			m_coverpoints;
	uint32_t								*m_bins_val;
	int32_t									m_n_bins;
	bool									m_coverage_valid;
	double									m_coverage;
};

} /* namespace vsc */


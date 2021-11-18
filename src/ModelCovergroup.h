/*
 * ModelCovergroup.h
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "IAccept.h"
#include "ModelCoverpoint.h"
#include "ModelCoverCross.h"

namespace vsc {

class ModelCovergroup : public IAccept {
public:
	ModelCovergroup();

	virtual ~ModelCovergroup();

	void add_coverpoint(ModelCoverpoint *cp) {
		m_coverpoints.push_back(ModelCoverpointUP(cp));
	}

	const std::vector<ModelCoverpointUP> &coverpoints() const {
		return m_coverpoints;
	}

	void add_cross(ModelCoverCross *cross) {
		m_crosses.push_back(ModelCoverCrossUP(cross));
	}

	const std::vector<ModelCoverCrossUP> &crosses() const {
		return m_crosses;
	}

	void sample();

	virtual void accept(IVisitor *v) override { v->visitModelCovergroup(this); }

private:
	std::vector<ModelCoverpointUP>			m_coverpoints;
	std::vector<ModelCoverCrossUP>			m_crosses;
};

} /* namespace vsc */


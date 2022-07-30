/*
 * ModelCovergroup.h
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IAccept.h"
#include "vsc/IModelCovergroup.h"
#include "ModelCoverItem.h"
#include "ModelCoverOpts.h"
#include "ModelCoverpoint.h"
#include "ModelCoverCross.h"

namespace vsc {

class ModelCovergroup;
using ModelCovergroupUP=std::unique_ptr<ModelCovergroup>;

class ModelCovergroup : 
	public virtual IModelCovergroup, 
	public virtual ModelCoverItem {
public:
	ModelCovergroup(const std::string &name);

	virtual ~ModelCovergroup();

	virtual void addCoverpoint(IModelCoverpoint *cp) override {
		m_coverpoints.push_back(IModelCoverpointUP(cp));
	}

	virtual const std::vector<IModelCoverpointUP> &coverpoints() const override {
		return m_coverpoints;
	}

	void addCross(IModelCoverCross *cross) {
		m_crosses.push_back(IModelCoverCrossUP(cross));
	}

	virtual const std::vector<IModelCoverCrossUP> &crosses() const override {
		return m_crosses;
	}

	virtual void finalize() override;

	virtual void sample() override;

	virtual double getCoverage() override;

	virtual void accept(IVisitor *v) override { v->visitModelCovergroup(this); }

private:
	std::vector<IModelCoverpointUP>			m_coverpoints;
	std::vector<IModelCoverCrossUP>			m_crosses;
};

} /* namespace vsc */


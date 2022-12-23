/*
 * ModelCovergroup.h
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IModelCovergroup.h"
#include "ModelCoverItem.h"
#include "ModelCoverOpts.h"
#include "ModelCoverpoint.h"
#include "ModelCoverCross.h"

namespace vsc {
namespace dm {

class ModelCovergroup;
using ModelCovergroupUP=std::unique_ptr<ModelCovergroup>;

class ModelCovergroup : 
	public virtual IModelCovergroup, 
	public virtual ModelCoverItem {
public:
	ModelCovergroup(const std::string &name);

	virtual ~ModelCovergroup();

	virtual void addCoverpoint(IModelCoverpoint *cp) override;

	virtual const std::vector<IModelCoverpointUP> &coverpoints() const override {
		return m_coverpoints;
	}

	virtual void addCross(IModelCoverCross *cross) override;

	virtual const std::vector<IModelCoverCrossUP> &crosses() const override {
		return m_crosses;
	}

	virtual void finalize() override;

	virtual void sample() override;

	virtual double getCoverage() override;

	virtual void coverageEvent() override;

	virtual void accept(IVisitor *v) override { v->visitModelCovergroup(this); }

private:
	double									m_coverage;
	bool									m_coverage_valid;
	std::vector<IModelCoverpointUP>			m_coverpoints;
	std::vector<IModelCoverCrossUP>			m_crosses;
};

}
} /* namespace vsc */


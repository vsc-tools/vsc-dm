/*
 * ModelCoverCross.h
 *
 *  Created on: Nov 16, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "IAccept.h"
#include "ModelCoverpoint.h"

namespace vsc {

class ModelCoverCross;
using ModelCoverCrossUP=std::unique_ptr<ModelCoverCross>;
class ModelCoverCross : public IAccept {
public:
	ModelCoverCross();

	virtual ~ModelCoverCross();

	virtual void accept(IVisitor *v) override { v->visitModelCoverCross(this); }

private:
	std::vector<ModelCoverpoint *>			m_coverpoints;
};

} /* namespace vsc */


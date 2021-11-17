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

private:
	ModelExprUP								m_target;
	std::string								m_name;
	ModelExprUP								m_iff;

	std::vector<IModelCoverpointBinsUP>		m_bins;

};

} /* namespace vsc */


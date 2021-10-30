/*
 * ModelExprRangelist.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ModelExprRange.h"

namespace vsc {

class ModelExprRangelist : public ModelExpr {
public:
	ModelExprRangelist();

	ModelExprRangelist(
			const std::vector<ModelExprRange *> &ranges);

	virtual ~ModelExprRangelist();

	const std::vector<ModelExprRangeUP> &ranges() const {
		return m_ranges;
	}

	virtual void accept(IVisitor *v) override { v->visitModelExprRangelist(this); }

private:
	std::vector<ModelExprRangeUP>		m_ranges;

};

} /* namespace vsc */


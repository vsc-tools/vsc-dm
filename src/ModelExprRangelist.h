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

class ModelExprRangelist;
using ModelExprRangelistUP=std::unique_ptr<ModelExprRangelist>;
class ModelExprRangelist : public ModelExpr {
public:
	ModelExprRangelist();

	ModelExprRangelist(
			const std::vector<ModelExprRange *> &ranges);

	virtual ~ModelExprRangelist();

	virtual int32_t width() const override { return m_width; }

	const std::vector<ModelExprRangeUP> &ranges() const {
		return m_ranges;
	}

	virtual void accept(IVisitor *v) override { v->visitModelExprRangelist(this); }

private:
	int32_t								m_width;
	std::vector<ModelExprRangeUP>		m_ranges;

};

} /* namespace vsc */


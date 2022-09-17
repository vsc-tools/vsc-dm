/*
 * ModelExprRangelist.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IModelExprRangelist.h"
#include "ModelExprRange.h"

namespace vsc {

class ModelExprRangelist;
using ModelExprRangelistUP=std::unique_ptr<ModelExprRangelist>;
class ModelExprRangelist : public IModelExprRangelist {
public:
	ModelExprRangelist();

	ModelExprRangelist(
			const std::vector<IModelExprRange *> &ranges);

	virtual ~ModelExprRangelist();

	virtual int32_t width() override { return m_width; }

	virtual const std::vector<IModelExprRangeUP> &ranges() const override {
		return m_ranges;
	}

	virtual const std::vector<IModelExprRangeUP> &getRanges() const override {
		return m_ranges;
	}

	virtual void addRange(IModelExprRange *range) override {
		m_ranges.push_back(IModelExprRangeUP(range));
	}

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprRangelist(this); }

private:
	int32_t								m_width;
	std::vector<IModelExprRangeUP>		m_ranges;

};

} /* namespace vsc */


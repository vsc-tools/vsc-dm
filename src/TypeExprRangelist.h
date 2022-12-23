/*
 * TypeExprRangelist.h
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExprRangelist.h"
#include "TypeExpr.h"

namespace vsc {
namespace dm {

class TypeExprRangelist : public ITypeExprRangelist, public virtual TypeExpr {
public:
	TypeExprRangelist();

	virtual ~TypeExprRangelist();

	virtual void optimize();

	virtual const std::vector<ITypeExprRangeUP> &getRanges() const override {
		return m_ranges;
	}

	virtual void addRange(ITypeExprRange *rng) override;

	virtual void accept(IVisitor *v) override { return v->visitTypeExprRangelist(this); }

private:
	std::vector<ITypeExprRangeUP>			m_ranges;

};

}
} /* namespace vsc */


/*
 * ModelExprEvaluator.h
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ModelVal.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class ModelExprEvaluator : public VisitorBase {
public:
	ModelExprEvaluator();

	virtual ~ModelExprEvaluator();

	ModelVal eval(IModelExpr *expr);

	virtual void visitModelExprBin(IModelExprBin *e) override;

	virtual void visitModelExprCond(IModelExprCond *e) override;

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override;

	virtual void visitModelExprIn(IModelExprIn *e) override;

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override;

	virtual void visitModelExprRange(IModelExprRange *e) override;

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override;

	virtual void visitModelExprRef(IModelExprRef *e) override;

	virtual void visitModelExprUnary(IModelExprUnary *e) override;

	virtual void visitModelExprVal(IModelExprVal *e) override;

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override;


private:
	ModelVal						m_val;
	std::vector<int32_t>			m_width_s;

};

} /* namespace vsc */


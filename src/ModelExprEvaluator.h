/*
 * ModelExprEvaluator.h
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ModelVal.h"
#include "VisitorBase.h"

namespace vsc {

class ModelExprEvaluator : public VisitorBase {
public:
	ModelExprEvaluator();

	virtual ~ModelExprEvaluator();

	ModelVal eval(IModelExpr *expr);

	virtual void visitModelExprBin(ModelExprBin *e) override;

	virtual void visitModelExprCond(ModelExprCond *e) override;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) override;

	virtual void visitModelExprIn(ModelExprIn *e) override;

	virtual void visitModelExprPartSelect(ModelExprPartSelect *e) override;

	virtual void visitModelExprRange(ModelExprRange *e) override;

	virtual void visitModelExprRangelist(ModelExprRangelist *e) override;

	virtual void visitModelExprRef(ModelExprRef *e) override;

	virtual void visitModelExprUnary(ModelExprUnary *e) override;

	virtual void visitModelExprVal(ModelExprVal *e) override;

	virtual void visitModelExprVecSubscript(ModelExprVecSubscript *e) override;


private:
	ModelVal						m_val;
	std::vector<int32_t>			m_width_s;

};

} /* namespace vsc */


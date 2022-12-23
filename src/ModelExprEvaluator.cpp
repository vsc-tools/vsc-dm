/*
 * ModelExprEvaluator.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#include "ModelExprEvaluator.h"

namespace vsc {
namespace dm {

ModelExprEvaluator::ModelExprEvaluator() {
	// TODO Auto-generated constructor stub

}

ModelExprEvaluator::~ModelExprEvaluator() {
	// TODO Auto-generated destructor stub
}

void ModelExprEvaluator::visitModelExprBin(IModelExprBin *e) {
	e->lhs()->accept(this);
	ModelVal lhs_v = m_val;
	e->rhs()->accept(this);
	ModelVal rhs_v = m_val;

	// TODO:
}

ModelVal ModelExprEvaluator::eval(IModelExpr *expr) {
	expr->accept(this);
	return m_val;
}

void ModelExprEvaluator::visitModelExprCond(IModelExprCond *e) {

}

void ModelExprEvaluator::visitModelExprFieldRef(IModelExprFieldRef *e) {
	m_val.set(e->field()->val());
}

void ModelExprEvaluator::visitModelExprIn(IModelExprIn *e) {

}

void ModelExprEvaluator::visitModelExprPartSelect(IModelExprPartSelect *e) {

}

void ModelExprEvaluator::visitModelExprRange(IModelExprRange *e) {

}

void ModelExprEvaluator::visitModelExprRangelist(IModelExprRangelist *e) {

}

void ModelExprEvaluator::visitModelExprRef(IModelExprRef *e) {

}

void ModelExprEvaluator::visitModelExprUnary(IModelExprUnary *e) {

}

void ModelExprEvaluator::visitModelExprVal(IModelExprVal *e) {

}

void ModelExprEvaluator::visitModelExprVecSubscript(IModelExprVecSubscript *e) {

}

}
} /* namespace vsc */

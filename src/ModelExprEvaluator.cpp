/*
 * ModelExprEvaluator.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#include "ModelExprEvaluator.h"

namespace vsc {

ModelExprEvaluator::ModelExprEvaluator() {
	// TODO Auto-generated constructor stub

}

ModelExprEvaluator::~ModelExprEvaluator() {
	// TODO Auto-generated destructor stub
}

void ModelExprEvaluator::visitModelExprBin(ModelExprBin *e) {
	e->lhs()->accept(this);
	ModelVal lhs_v = m_val;
	e->rhs()->accept(this);
	ModelVal rhs_v = m_val;

	// TODO:
}

ModelVal ModelExprEvaluator::eval(ModelExpr *expr) {
	expr->accept(this);
	return m_val;
}

void ModelExprEvaluator::visitModelExprCond(ModelExprCond *e) {

}

void ModelExprEvaluator::visitModelExprFieldRef(ModelExprFieldRef *e) {
	m_val = e->field()->val();
}

void ModelExprEvaluator::visitModelExprIn(ModelExprIn *e) {

}

void ModelExprEvaluator::visitModelExprPartSelect(ModelExprPartSelect *e) {

}

void ModelExprEvaluator::visitModelExprRange(ModelExprRange *e) {

}

void ModelExprEvaluator::visitModelExprRangelist(ModelExprRangelist *e) {

}

void ModelExprEvaluator::visitModelExprRef(ModelExprRef *e) {

}

void ModelExprEvaluator::visitModelExprUnary(ModelExprUnary *e) {

}

void ModelExprEvaluator::visitModelExprVal(ModelExprVal *e) {

}

void ModelExprEvaluator::visitModelExprVecSubscript(ModelExprVecSubscript *e) {

}


} /* namespace vsc */

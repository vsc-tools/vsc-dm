/*
 * GetModelValVisitor.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#include "GetModelValVisitor.h"

namespace vsc {

GetModelValVisitor::GetModelValVisitor() : m_ctx(0), m_val(64) {
	// TODO Auto-generated constructor stub

}

GetModelValVisitor::~GetModelValVisitor() {
	// TODO Auto-generated destructor stub
}

ModelVal GetModelValVisitor::value(
		ModelField			*ctx,
		ModelExpr			*expr) {
	m_ctx = ctx;
	expr->accept(this);
	return m_val;
}

void GetModelValVisitor::visitModelExprVecSubscript(IModelExprVecSubscript *e) {
	e->expr()->accept(this);

	// TODO: Save field reference that we're indexing

	e->expr()->accept(this);

	// TODO: Save value that we're indexing the field with


}

} /* namespace vsc */

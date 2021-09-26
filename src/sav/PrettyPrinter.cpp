/*
 * PrettyPrinter.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: ballance
 */

#include "sav/PrettyPrinter.h"

#include <stdio.h>
#include <stdarg.h>

namespace vsc {

PrettyPrinter::PrettyPrinter(const std::string &ind) : m_ind(ind) {
	// TODO Auto-generated constructor stub

}

PrettyPrinter::~PrettyPrinter() {
	// TODO Auto-generated destructor stub
}

const std::string &PrettyPrinter::operator ()(IAccept *e) {
	m_str.clear();
	e->accept(this);
	return m_str;
}

void PrettyPrinter::visitConstraintBlock(ConstraintBlock *c) { }

void PrettyPrinter::visitConstraintIf(ConstraintIf *c) { }

void PrettyPrinter::visitConstraintScope(ConstraintScope *c) { }

void PrettyPrinter::visitConstraintSoft(ConstraintSoft *c) { }

void PrettyPrinter::visitConstraintStmtEnter(ConstraintStmt *c) { }

void PrettyPrinter::visitConstraintStmtLeave(ConstraintStmt *c) { }

void PrettyPrinter::visitConstraintExpr(ConstraintExpr *c) { }

void PrettyPrinter::visitExprBin(ExprBin *e) {
	e->lhs()->accept(this);


}

void PrettyPrinter::visitExprCond(ExprCond *e) { }

void PrettyPrinter::visitExprDynamicConstraintRef(ExprDynamicConstraintRef *e) { }

void PrettyPrinter::visitExprFieldRef(ExprFieldRef *e) { }

void PrettyPrinter::visitExprListSubscript(ExprListSubscript *e) { }

void PrettyPrinter::visitExprRange(ExprRange *e) {

}

void PrettyPrinter::visitExprRangelist(ExprRangelist *e) {

}

void PrettyPrinter::visitExprUnary(ExprUnary *e) {

}

void PrettyPrinter::visitFieldComposite(FieldComposite *f) {

}

void PrettyPrinter::visitFieldScalar(FieldScalar *f) {

}

void PrettyPrinter::inc_indent() {
	m_ind += "    ";
}

void PrettyPrinter::dec_indent() {
	if (m_ind.size() > 4) {
		m_ind = m_ind.substr(4);
	} else {
		m_ind.clear();
	}
}

void PrettyPrinter::println(const char *fmt, ...) {
	char tmp[4096];
	va_list ap;
	va_start(ap, fmt);

	vsprintf(tmp, fmt, ap);
	m_str += m_ind;
	m_str += tmp;
	m_str += "\n";

	va_end(ap);
}

void PrettyPrinter::print(const char *fmt, ...) {
	char tmp[4096];
	va_list ap;
	va_start(ap, fmt);

	vsprintf(tmp, fmt, ap);
	m_str += tmp;

	va_end(ap);
}

void PrettyPrinter::printind(const char *fmt, ...) {
	char tmp[4096];
	va_list ap;
	va_start(ap, fmt);

	vsprintf(tmp, fmt, ap);
	m_str += m_ind;
	m_str += tmp;

	va_end(ap);
}

} /* namespace vsc */

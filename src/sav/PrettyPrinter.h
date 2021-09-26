/*
 * PrettyPrinter.h
 *
 *  Created on: Aug 2, 2020
 *      Author: ballance
 */

#pragma once
#include "../IAccept.h"
#include "VisitorBase.h"

namespace vsc {

class PrettyPrinter : public VisitorBase {
public:
	PrettyPrinter(const std::string &ind);

	virtual ~PrettyPrinter();

	const std::string &operator()(IAccept *e);

	virtual void visitConstraintBlock(ConstraintBlock *c) override;

	virtual void visitConstraintIf(ConstraintIf *c) override;

	virtual void visitConstraintScope(ConstraintScope *c) override;

	virtual void visitConstraintSoft(ConstraintSoft *c) override;

	virtual void visitConstraintStmtEnter(ConstraintStmt *c) override;

	virtual void visitConstraintStmtLeave(ConstraintStmt *c) override;

	virtual void visitConstraintExpr(ConstraintExpr *c) override;

	virtual void visitExprBin(ExprBin *e) override;

	virtual void visitExprCond(ExprCond *e) override;

	virtual void visitExprDynamicConstraintRef(ExprDynamicConstraintRef *e) override;

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

	virtual void visitExprListSubscript(ExprListSubscript *e) override;

	virtual void visitExprRange(ExprRange *e) override;

	virtual void visitExprRangelist(ExprRangelist *e) override;

	virtual void visitExprUnary(ExprUnary *e) override;

	virtual void visitFieldComposite(FieldComposite *f) override;

	virtual void visitFieldScalar(FieldScalar *f) override;

protected:

	void inc_indent();

	void dec_indent();

	void println(const char *fnt, ...);

	void print(const char *fmt, ...);

	void printind(const char *fmt, ...);


private:
	std::string				m_ind;
	std::string				m_str;
};

} /* namespace vsc */


/*
 * TypeExprBin.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeExprBin.h"

namespace vsc {

class TypeExprBin : public ITypeExprBin {
public:
	TypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs);

	virtual ~TypeExprBin();

	virtual ITypeExpr *lhs() const override {
		return m_lhs.get();
	}

	virtual BinOp op() const override {
		return m_op;
	}

	virtual ITypeExpr *rhs() const override {
		return m_rhs.get();
	}

	virtual void accept(IVisitor *v) { v->visitTypeExprBin(this); }

private:
	ITypeExprUP				m_lhs;
	BinOp					m_op;
	ITypeExprUP				m_rhs;

};

} /* namespace vsc */


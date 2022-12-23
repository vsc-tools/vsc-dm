/*
 * TypeExprRange.h
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/dm/ITypeExprRange.h"
#include "TypeExpr.h"

namespace vsc {
namespace dm {

class TypeExprRange : public ITypeExprRange, public virtual TypeExpr {
public:
	TypeExprRange(
			bool		is_single,
			ITypeExpr	*lower,
			ITypeExpr	*upper);

	virtual ~TypeExprRange();

	virtual bool isSingle() const override { return m_is_single; }

	virtual ITypeExpr *lower() const override { return m_lower.get(); }

	virtual ITypeExpr *upper() const override { return m_upper.get(); }

	virtual void accept(IVisitor *v) override { v->visitTypeExprRange(this); }

private:
	bool				m_is_single;
	ITypeExprUP			m_lower;
	ITypeExprUP			m_upper;
};

}
} /* namespace vsc */


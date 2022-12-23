/*
 * TaskEvalExpr.h
 *
 *  Created on: Jun 30, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelVal.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class TaskEvalTypeExpr : public VisitorBase {
public:

	TaskEvalTypeExpr() : m_val(0), m_resolved(false) { }

	virtual ~TaskEvalTypeExpr() { }

	bool eval(IModelVal *val, ITypeExpr *expr) {
		m_val = val;
		m_resolved = true;

		expr->accept(m_this);

		return m_resolved;
	}

	virtual void visitTypeExprVal(ITypeExprVal *e) override {
		m_val->set(e->val());
	}

protected:
	IModelVal			*m_val;
	bool				m_resolved;
};

}
}

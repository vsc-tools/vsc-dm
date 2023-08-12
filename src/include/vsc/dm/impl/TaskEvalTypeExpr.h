/*
 * TaskEvalExpr.h
 *
 *  Created on: Jun 30, 2022
 *      Author: mballance
 * 
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
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
		// TODO:
		fprintf(stdout, "TODO: handle ValData\n");
//		m_val->set(e->val());
	}

protected:
	IModelVal			*m_val;
	bool				m_resolved;
};

}
}

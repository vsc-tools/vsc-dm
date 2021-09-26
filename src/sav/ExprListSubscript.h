
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * ExprArraySubscript.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRLISTSUBSCRIPT_H_
#define SRC_EXPR_EXPRLISTSUBSCRIPT_H_
#include "sav/Expr.h"
#include "sav/FieldList.h"

namespace vsc {

class ExprListSubscript : public Expr {
public:
	ExprListSubscript(
			FieldList		*lhs,
			Expr			*rhs);

	virtual ~ExprListSubscript();

	FieldList *lhs() const { return m_lhs.get(); }

	Expr *rhs() const { return m_rhs.get(); }

	virtual void accept(IVisitor *v) { v->visitExprListSubscript(this); }

private:
	FieldListSP				m_lhs;
	ExprSP					m_rhs;
};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRLISTSUBSCRIPT_H_ */

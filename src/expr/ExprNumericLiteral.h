
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
 * ExprNumericLiteral.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "expr/Expr.h"
#include "expr/ExprValNumeric.h"

namespace vsc {

class ExprNumericLiteral : public Expr {
public:
	ExprNumericLiteral(ExprValNumeric *		val);

	ExprNumericLiteral(ExprValNumericSP		val);

	virtual ~ExprNumericLiteral();

	ExprValSP val() const { return m_val; }

	ExprValNumericSP val_num() const { return m_val; }

	uint64_t val_u() const { return m_val->val_u(); }

	int64_t val_s() const { return m_val->val_s(); }

	virtual void accept(IVisitor *v) { v->visitExprNumericLiteral(this); }

public:
	static ExprSP			ZERO;
	static ExprSP			ONE;

private:

	ExprValNumericSP		m_val;

};

} /* namespace vsc */


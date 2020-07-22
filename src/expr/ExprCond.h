
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
 * ExprCond.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#pragma once
#include "Expr.h"

namespace vsc {

class ExprCond : public Expr {
public:

	ExprCond(
			Expr		*cond,
			Expr		*true_e,
			Expr		*false_e
			);

	ExprCond(
			ExprSP		cond,
			ExprSP		true_e,
			ExprSP		false_e
			);

	virtual ~ExprCond();

	Expr *cond() const { return m_cond.get(); }

	Expr *true_e() const { return m_true_e.get(); }

	Expr *false_e() const { return m_false_e.get(); }

	virtual void accept(IVisitor *v) { v->visitExprCond(this); }

private:
	ExprSP				m_cond;
	ExprSP				m_true_e;
	ExprSP				m_false_e;

};

} /* namespace vsc */


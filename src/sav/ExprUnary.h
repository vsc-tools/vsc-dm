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
 * ExprUnary.h
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#pragma once
#include "sav/Expr.h"
#include "sav/ExprUnaryOp.h"

namespace vsc {

class ExprUnary : public Expr {
public:
	ExprUnary(
			ExprUnaryOp		op,
			ExprSP			rhs);

	virtual ~ExprUnary();

	ExprUnaryOp op() const { return m_op; }

	ExprSP rhs() const { return m_rhs; }

	virtual void accept(IVisitor *v) { v->visitExprUnary(this); }

private:
	ExprUnaryOp				m_op;
	ExprSP					m_rhs;
};

}


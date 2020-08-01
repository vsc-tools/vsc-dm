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
 * ExprRange.h
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#pragma once
#include "Expr.h"

namespace vsc {

class ExprRange;
typedef std::shared_ptr<ExprRange> ExprRangeSP;

class ExprRange : public Expr {
public:
	ExprRange(
			ExprSP		lhs,
			ExprSP		rhs);

	virtual ~ExprRange();

	ExprSP lhs() const { return m_lhs; }

	ExprSP rhs() const { return m_rhs; }

	virtual void accept(IVisitor *v) { v->visitExprRange(this); }

	static ExprRangeSP toRange(ExprSP r) {
		return std::dynamic_pointer_cast<ExprRange>(r);
	}

private:
	ExprSP				m_lhs;
	ExprSP				m_rhs;
};


} /* namespace vsc */


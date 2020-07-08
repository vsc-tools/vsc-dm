
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
 * ExprEvaluator.h
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRNUMERICEVALUATOR_H_
#define SRC_EXPR_EXPRNUMERICEVALUATOR_H_
#include "VisitorBase.h"
#include "expr/ExprValNumeric.h"

namespace vsc {

class ExprNumericEvaluator : public VisitorBase {
public:
	ExprNumericEvaluator();

	virtual ~ExprNumericEvaluator();

	ExprValSP eval(Expr *e);

	ExprValNumericSP eval_num(Expr *e);

	virtual void visitExprBin(ExprBin *e) override;

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

private:
	ExprValSP _eval(ExprSP e);

private:
	ExprValNumericSP			m_val;

};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRNUMERICEVALUATOR_H_ */

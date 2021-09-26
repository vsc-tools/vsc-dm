
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
 * ExprDynamicConstraintRef.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRDYNAMICCONSTRAINTREF_H_
#define SRC_EXPR_EXPRDYNAMICCONSTRAINTREF_H_
#include "sav/ConstraintBlock.h"
#include "sav/Expr.h"

namespace vsc {

class ExprDynamicConstraintRef : public Expr {
public:
	ExprDynamicConstraintRef(
			ConstraintBlock			*constraint);

	virtual ~ExprDynamicConstraintRef();

	ConstraintBlock *constraint() const { return m_constraint.get(); }

	virtual void accept(IVisitor *v) { v->visitExprDynamicConstraintRef(this); }

private:
	ConstraintBlockSP				m_constraint;

};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRDYNAMICCONSTRAINTREF_H_ */

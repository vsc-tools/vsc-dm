
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
 * VisitorBase.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#include "VisitorBase.h"

namespace vsc {

VisitorBase::VisitorBase() {
	// TODO Auto-generated constructor stub

}

VisitorBase::~VisitorBase() {
	// TODO Auto-generated destructor stub
}

void VisitorBase::visitConstraintBlock(ConstraintBlock *c) {
	visitConstraintScope(c);
}

void VisitorBase::visitConstraintIf(ConstraintIf *c) {
	visitConstraintStmtEnter(c);
	c->cond()->accept(this);
	c->true_s()->accept(this);
	if (c->false_s()) {
		c->false_s()->accept(this);
	}
	visitConstraintStmtLeave(c);
}

void VisitorBase::visitConstraintScope(ConstraintScope *c) {
	for (std::vector<ConstraintStmtSP>::const_iterator it=c->constraints().begin();
			it!=c->constraints().end(); it++) {
		(*it)->accept(this);
	}
}

void VisitorBase::visitConstraintStmtEnter(ConstraintStmt *c) {

}

void VisitorBase::visitConstraintStmtLeave(ConstraintStmt *c) {

}

void VisitorBase::visitConstraintExpr(ConstraintExpr *c) {
	visitConstraintStmtEnter(c);
	c->expr()->accept(this);
	visitConstraintStmtLeave(c);
}

void VisitorBase::visitExprBin(ExprBin *e) {
	e->lhs()->accept(this);
	e->rhs()->accept(this);
}

void VisitorBase::visitExprCond(ExprCond *e) {
	e->cond()->accept(this);
	e->true_e()->accept(this);
	e->false_e()->accept(this);
}

void VisitorBase::visitExprDynamicConstraintRef(ExprDynamicConstraintRef *e) {
	e->constraint()->accept(this);
}

void VisitorBase::visitExprFieldRef(ExprFieldRef *e) {
	e->field()->accept(this);
}

void VisitorBase::visitExprListSubscript(ExprListSubscript *e) {
	e->lhs()->accept(this);
	e->rhs()->accept(this);
}

void VisitorBase::visitFieldComposite(FieldComposite *f) {
	for (std::vector<FieldSP>::const_iterator it=f->children().begin();
			it!=f->children().end(); it++) {
		(*it)->accept(this);
	}
	for (std::vector<ConstraintBlockSP>::const_iterator it=f->constraints().begin();
			it!=f->constraints().end(); it++) {
		(*it)->accept(this);
	}

}

void VisitorBase::visitFieldScalar(FieldScalar *f) {

}


} /* namespace vsc */

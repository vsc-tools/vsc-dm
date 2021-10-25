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

#include "Debug.h"
#include "VisitorBase.h"

#undef EN_DEBUG_VISITOR_BASE

#ifdef EN_DEBUG_VISITOR_BASE
DEBUG_SCOPE(VisitorBase)
#define DEBUG_ENTER(fmt, ...) \
	DEBUG_ENTER_BASE(VisitorBase, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
	DEBUG_LEAVE_BASE(VisitorBase, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
	DEBUG_BASE(VisitorBase, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

VisitorBase::VisitorBase() {
	// TODO Auto-generated constructor stub

}

VisitorBase::~VisitorBase() {
	// TODO Auto-generated destructor stub
}

void VisitorBase::visitDataTypeInt(DataTypeInt *t) {

}

void VisitorBase::visitDataTypeStruct(DataTypeStruct *t) {

}

void VisitorBase::visitModelConstraint(ModelConstraint *c) {

}

void VisitorBase::visitModelConstraintExpr(ModelConstraintExpr *c) {
	DEBUG_ENTER("visitModelConstraintExpr");
	visitModelConstraint(c);
	c->expr()->accept(this);
	DEBUG_LEAVE("visitModelConstraintExpr");
}

void VisitorBase::visitModelConstraintScope(ModelConstraintScope *c) {
	DEBUG_ENTER("visitModelConstraintScope n=%d", c->constraints().size());
	for (auto it=c->constraints().begin();
			it!=c->constraints().end(); it++) {
		(*it)->accept(this);
	}
	DEBUG_LEAVE("visitModelConstraintScope n=%d", c->constraints().size());
}

void VisitorBase::visitModelConstraintSoft(ModelConstraintSoft *c) {
	DEBUG_ENTER("visitModelConstraintSoft");
	c->constraint()->accept(this);
	DEBUG_LEAVE("visitModelConstraintSoft");
}

void VisitorBase::visitModelExprBin(ModelExprBin *e) {
	DEBUG_ENTER("visitModelExprBin");
	e->lhs()->accept(this);
	e->rhs()->accept(this);
	DEBUG_LEAVE("visitModelExprBin");
}

void VisitorBase::visitModelExprFieldRef(ModelExprFieldRef *e) {
	DEBUG_ENTER("visitModelExprFieldRef");
	e->field()->accept(this);
	DEBUG_LEAVE("visitModelExprFieldRef");
}

void VisitorBase::visitModelField(ModelField *f) {
	DEBUG_ENTER("visitModelField %s n_fields=%d n_constraints=%d",
			f->name().c_str(),
			f->fields().size(),
			f->constraints().size());
	if (f->datatype()) {
		f->datatype()->accept(this);
	}
	for (auto it=f->fields().begin();
			it!=f->fields().end(); it++) {
		(*it)->accept(this);
	}
	for (auto it=f->constraints().begin();
			it!=f->constraints().end(); it++) {
		(*it)->accept(this);
	}
	DEBUG_LEAVE("visitModelField %s n_fields=%d n_constraints=%d",
			f->name().c_str(),
			f->fields().size(),
			f->constraints().size());
}

void VisitorBase::visitModelFieldRoot(ModelFieldRoot *f) {
	visitModelField(f);
}

void VisitorBase::visitModelFieldType(ModelFieldType *f) {
	visitModelField(f);

}

void VisitorBase::visitTypeField(TypeField *f) {
}

} /* namespace vsc */

/*
 * Copyright 2019-2021 Matthew Ballance and contributors
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

void VisitorBase::visitDataTypeInt(IDataTypeInt *t) {

}

void VisitorBase::visitDataTypeStruct(IDataTypeStruct *t) {

}

void VisitorBase::visitModelConstraint(IModelConstraint *c) {

}

void VisitorBase::visitModelConstraintBlock(IModelConstraintBlock *c) {
	DEBUG_ENTER("visitModelConstraintBlock");
	visitModelConstraintScope(c);
	DEBUG_LEAVE("visitModelConstraintBlock");
}

void VisitorBase::visitModelConstraintExpr(IModelConstraintExpr *c) {
	DEBUG_ENTER("visitModelConstraintExpr");
	visitModelConstraint(c);
	c->expr()->accept(this);
	DEBUG_LEAVE("visitModelConstraintExpr");
}

void VisitorBase::visitModelConstraintIf(IModelConstraintIf *c) {
	DEBUG_ENTER("visitModelConstraintIf");
	c->cond()->accept(this);
	c->getTrue()->accept(this);
	if (c->getFalse()) {
		c->getFalse()->accept(this);
	}
	DEBUG_LEAVE("visitModelConstraintIf");
}

void VisitorBase::visitModelConstraintImplies(IModelConstraintImplies *c) {
	DEBUG_ENTER("visitModelConstraintImplies");
	c->cond()->accept(this);
	c->body()->accept(this);
	DEBUG_LEAVE("visitModelConstraintImplies");
}

void VisitorBase::visitModelConstraintScope(IModelConstraintScope *c) {
	DEBUG_ENTER("visitModelConstraintScope n=%d", c->constraints().size());
	for (auto it=c->constraints().begin();
			it!=c->constraints().end(); it++) {
		(*it)->accept(this);
	}
	DEBUG_LEAVE("visitModelConstraintScope n=%d", c->constraints().size());
}

void VisitorBase::visitModelConstraintSoft(IModelConstraintSoft *c) {
	DEBUG_ENTER("visitModelConstraintSoft");
	c->constraint()->accept(this);
	DEBUG_LEAVE("visitModelConstraintSoft");
}

void VisitorBase::visitModelCoverCross(ModelCoverCross *c) {
	DEBUG_ENTER("visitModelCoverCross");

	DEBUG_LEAVE("visitModelCoverCross");
}

void VisitorBase::visitModelCovergroup(ModelCovergroup *c) {
	DEBUG_ENTER("visitModelCovergroup");
	for (auto it=c->coverpoints().begin(); it!=c->coverpoints().end(); it++) {
		(*it)->accept(this);
	}
	for (auto it=c->crosses().begin(); it!=c->crosses().end(); it++) {
		(*it)->accept(this);
	}

	DEBUG_LEAVE("visitModelCovergroup");
}

void VisitorBase::visitModelCoverpoint(ModelCoverpoint *c) {
	DEBUG_ENTER("visitModelCoverpoint");
	c->target()->accept(this);
	if (c->iff()) {
		c->iff()->accept(this);
	}
	DEBUG_LEAVE("visitModelCoverpoint");
}

void VisitorBase::visitModelExprBin(ModelExprBin *e) {
	DEBUG_ENTER("visitModelExprBin");
	e->lhs()->accept(this);
	e->rhs()->accept(this);
	DEBUG_LEAVE("visitModelExprBin");
}

void VisitorBase::visitModelExprCond(ModelExprCond *e) {
	e->cond()->accept(this);
	e->true_e()->accept(this);
	e->false_e()->accept(this);
}

void VisitorBase::visitModelExprFieldRef(ModelExprFieldRef *e) {
	DEBUG_ENTER("visitModelExprFieldRef");
	e->field()->accept(this);
	DEBUG_LEAVE("visitModelExprFieldRef");
}

void VisitorBase::visitModelExprIn(ModelExprIn *e) {
	DEBUG_ENTER("visitModelExprIn");
	e->lhs()->accept(this);
	e->rangelist()->accept(this);
	DEBUG_LEAVE("visitModelExprIn");
}

void VisitorBase::visitModelExprPartSelect(ModelExprPartSelect *e) {
	DEBUG_ENTER("visitModelExprPartSelect");
	e->lhs()->accept(this);
	DEBUG_LEAVE("visitModelExprPartSelect");
}

void VisitorBase::visitModelExprRange(ModelExprRange *e) {
	DEBUG_ENTER("visitModelExprRange");
	e->lower()->accept(this);
	if (e->upper()) {
		e->upper()->accept(this);
	}
	DEBUG_LEAVE("visitModelExprRange");
}

void VisitorBase::visitModelExprRangelist(ModelExprRangelist *e) {
	DEBUG_ENTER("visitModelExprRangelist");
	for (auto it=e->ranges().begin(); it!=e->ranges().end(); it++) {
		(*it)->accept(this);
	}
	DEBUG_LEAVE("visitModelExprRangelist");
}

void VisitorBase::visitModelExprRef(ModelExprRef *e) {
	DEBUG_ENTER("visitModelExprRef");
	e->expr()->accept(this);
	DEBUG_LEAVE("visitModelExprRef");
}

void VisitorBase::visitModelExprUnary(ModelExprUnary *e) {
	DEBUG_ENTER("visitModelExprUnary");
	e->expr()->accept(this);
	DEBUG_LEAVE("visitModelExprUnary");
}

void VisitorBase::visitModelExprVal(ModelExprVal *e) {
	DEBUG_ENTER("visitModelExprVal");

	DEBUG_LEAVE("visitModelExprVal");
}

void VisitorBase::visitModelExprVecSubscript(ModelExprVecSubscript *e) {
	DEBUG_ENTER("visitModelExprVecSubscript");
	e->expr()->accept(this);
	e->subscript()->accept(this);
	DEBUG_LEAVE("visitModelExprVecSubscript");
}

void VisitorBase::visitModelField(IModelField *f) {
	DEBUG_ENTER("visitModelField %s n_fields=%d n_constraints=%d",
			f->name().c_str(),
			f->fields().size(),
			f->constraints().size());
	if (f->getDataType()) {
		f->getDataType()->accept(this);
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

void VisitorBase::visitModelFieldVec(ModelFieldVec *f) {
	f->size()->accept(this);
	visitModelField(f);
}

void VisitorBase::visitModelFieldVecRoot(ModelFieldVecRoot *f) {
	visitModelFieldVec(f);
}

void VisitorBase::visitTypeField(TypeField *f) {
}

} /* namespace vsc */

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
 * VisitorBase.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#pragma once
#include "vsc/IVisitor.h"

#include "vsc/IDataTypeInt.h"
#include "vsc/IDataTypeStruct.h"

#include "vsc/IModelConstraintBlock.h"
#include "vsc/IModelConstraintExpr.h"
#include "vsc/IModelConstraintIf.h"
#include "vsc/IModelConstraintImplies.h"
#include "vsc/IModelConstraintScope.h"
#include "vsc/IModelConstraintSoft.h"

#include "ModelCoverCross.h"
#include "ModelCovergroup.h"
#include "ModelCoverpoint.h"

#include "ModelExprBin.h"
#include "ModelExprCond.h"
#include "ModelExprFieldRef.h"
#include "ModelExprIn.h"
#include "ModelExprPartSelect.h"
#include "ModelExprRange.h"
#include "ModelExprRangelist.h"
#include "ModelExprRef.h"
#include "ModelExprVecSubscript.h"
#include "ModelExprUnary.h"
#include "ModelExprVal.h"

#include "ModelFieldRoot.h"
#include "ModelFieldType.h"
#include "ModelFieldVec.h"
#include "ModelFieldVecRoot.h"
#include "TypeField.h"

namespace vsc {

class VisitorBase : public virtual IVisitor {
public:

	VisitorBase();

	virtual ~VisitorBase();

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

	virtual void visitModelConstraint(IModelConstraint *c) override;

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override;

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override;

	virtual void visitModelConstraintIf(IModelConstraintIf *c) override;

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override;

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override;

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override;

	virtual void visitModelCoverCross(ModelCoverCross *c) override;

	virtual void visitModelCovergroup(ModelCovergroup *c) override;

	virtual void visitModelCoverpoint(ModelCoverpoint *c) override;

	virtual void visitModelExprBin(ModelExprBin *e) override;

	virtual void visitModelExprCond(ModelExprCond *e) override;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) override;

	virtual void visitModelExprIn(ModelExprIn *e) override;

	virtual void visitModelExprPartSelect(ModelExprPartSelect *e) override;

	virtual void visitModelExprRange(ModelExprRange *e) override;

	virtual void visitModelExprRangelist(ModelExprRangelist *e) override;

	virtual void visitModelExprRef(ModelExprRef *e) override;

	virtual void visitModelExprUnary(ModelExprUnary *e) override;

	virtual void visitModelExprVal(ModelExprVal *e) override;

	virtual void visitModelExprVecSubscript(ModelExprVecSubscript *e) override;

	virtual void visitModelField(IModelField *f) override;

	virtual void visitModelFieldRoot(ModelFieldRoot *f) override;

	virtual void visitModelFieldType(ModelFieldType *f) override;

	virtual void visitModelFieldVec(ModelFieldVec *f) override;

	virtual void visitModelFieldVecRoot(ModelFieldVecRoot *f) override;

	virtual void visitTypeField(TypeField *f) override;

};

} /* namespace vsc */


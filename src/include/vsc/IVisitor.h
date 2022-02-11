
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
 * IVisitor.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#pragma once

namespace vsc {

class IDataTypeInt;
class IDataTypeStruct;

class IModelConstraint;
class IModelConstraintBlock;
class IModelConstraintExpr;
class IModelConstraintIf;
class IModelConstraintImplies;
class IModelConstraintScope;
class IModelConstraintSoft;

class ModelCoverCross;
class ModelCovergroup;
class ModelCoverpoint;

class ModelExprBin;
class ModelExprCond;
class ModelExprFieldRef;
class ModelExprIn;
class ModelExprPartSelect;
class ModelExprRange;
class ModelExprRangelist;
class ModelExprRef;
class ModelExprVecSubscript;
class ModelExprUnary;
class ModelExprVal;

class IModelField;
class ModelFieldRoot;
class ModelFieldType;
class ModelFieldVec;
class ModelFieldVecRoot;

class TypeField;

class IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitDataTypeInt(IDataTypeInt *t) = 0;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) = 0;

	virtual void visitModelConstraint(IModelConstraint *c) = 0;

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) = 0;

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) = 0;

	virtual void visitModelConstraintIf(IModelConstraintIf *c) = 0;

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) = 0;

	virtual void visitModelConstraintScope(IModelConstraintScope *c) = 0;

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) = 0;

	virtual void visitModelCoverCross(ModelCoverCross *c) = 0;

	virtual void visitModelCovergroup(ModelCovergroup *c) = 0;

	virtual void visitModelCoverpoint(ModelCoverpoint *c) = 0;

	virtual void visitModelExprBin(ModelExprBin *e) = 0;

	virtual void visitModelExprCond(ModelExprCond *e) = 0;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) = 0;

	virtual void visitModelExprIn(ModelExprIn *e) = 0;

	virtual void visitModelExprPartSelect(ModelExprPartSelect *e) = 0;

	virtual void visitModelExprRange(ModelExprRange *e) = 0;

	virtual void visitModelExprRangelist(ModelExprRangelist *e) = 0;

	virtual void visitModelExprRef(ModelExprRef *e) = 0;

	virtual void visitModelExprUnary(ModelExprUnary *e) = 0;

	virtual void visitModelExprVal(ModelExprVal *e) = 0;

	virtual void visitModelExprVecSubscript(ModelExprVecSubscript *e) = 0;

	virtual void visitModelField(IModelField *f) = 0;

	virtual void visitModelFieldRoot(ModelFieldRoot *f) = 0;

	virtual void visitModelFieldType(ModelFieldType *f) = 0;

	virtual void visitModelFieldVec(ModelFieldVec *f) = 0;

	virtual void visitModelFieldVecRoot(ModelFieldVecRoot *f) = 0;

	virtual void visitTypeField(TypeField *f) = 0;

};

}



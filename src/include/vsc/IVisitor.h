
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

class IModelExprBin;
class IModelExprCond;
class IModelExprFieldRef;
class IModelExprIn;
class IModelExprPartSelect;
class IModelExprRange;
class IModelExprRangelist;
class IModelExprRef;
class IModelExprVecSubscript;
class IModelExprUnary;
class IModelExprVal;

class IModelField;
class IModelFieldRoot;
class IModelFieldType;
class ModelFieldVec;
class ModelFieldVecRoot;

class ITypeConstraint;
class ITypeConstraintBlock;
class ITypeConstraintExpr;
class ITypeConstraintScope;
class ITypeExpr;
class ITypeExprBin;
class ITypeExprFieldRef;
class ITypeExprVal;
class ITypeField;

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

	virtual void visitModelExprBin(IModelExprBin *e) = 0;

	virtual void visitModelExprCond(IModelExprCond *e) = 0;

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) = 0;

	virtual void visitModelExprIn(IModelExprIn *e) = 0;

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) = 0;

	virtual void visitModelExprRange(IModelExprRange *e) = 0;

	virtual void visitModelExprRangelist(IModelExprRangelist *e) = 0;

	virtual void visitModelExprRef(IModelExprRef *e) = 0;

	virtual void visitModelExprUnary(IModelExprUnary *e) = 0;

	virtual void visitModelExprVal(IModelExprVal *e) = 0;

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) = 0;

	virtual void visitModelField(IModelField *f) = 0;

	virtual void visitModelFieldRoot(IModelFieldRoot *f) = 0;

	virtual void visitModelFieldType(IModelFieldType *f) = 0;

	virtual void visitModelFieldVec(ModelFieldVec *f) = 0;

	virtual void visitModelFieldVecRoot(ModelFieldVecRoot *f) = 0;

	virtual void visitTypeExprBin(ITypeExprBin *e) = 0;

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) = 0;

	virtual void visitTypeExprVal(ITypeExprVal *e) = 0;

	virtual void visitTypeField(ITypeField *f) = 0;


};

}



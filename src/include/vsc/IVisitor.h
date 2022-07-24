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

class IDataTypeEnum;
class IDataTypeInt;
class IDataTypeStruct;

class IModelConstraint;
class IModelConstraintBlock;
class IModelConstraintExpr;
class IModelConstraintIfElse;
class IModelConstraintImplies;
class IModelConstraintScope;
class IModelConstraintSoft;
class IModelConstraintSubst;
class IModelConstraintUnique;

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
class IModelFieldRef;
class IModelFieldRoot;
class IModelFieldType;
class IModelFieldVec;
class IModelFieldVecRoot;

class ITypeConstraint;
class ITypeConstraintBlock;
class ITypeConstraintExpr;
class ITypeConstraintIfElse;
class ITypeConstraintImplies;
class ITypeConstraintScope;
class ITypeConstraintSoft;
class ITypeConstraintUnique;
class ITypeExpr;
class ITypeExprBin;
class ITypeExprFieldRef;
class ITypeExprRange;
class ITypeExprRangelist;
class ITypeExprVal;
class ITypeField;
class ITypeFieldPhy;
class ITypeFieldRef;
class ITypeFieldVec;

class IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitDataTypeEnum(IDataTypeEnum *t) = 0;

	virtual void visitDataTypeInt(IDataTypeInt *t) = 0;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) = 0;

	virtual void visitModelConstraint(IModelConstraint *c) = 0;

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) = 0;

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) = 0;

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) = 0;

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) = 0;

	virtual void visitModelConstraintScope(IModelConstraintScope *c) = 0;

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) = 0;

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) = 0;

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) = 0;

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

	virtual void visitModelFieldRef(IModelFieldRef *f) = 0;

	virtual void visitModelFieldRefRoot(IModelFieldRef *f) = 0;

	virtual void visitModelFieldRefType(IModelFieldRef *f) = 0;

	virtual void visitModelFieldRoot(IModelFieldRoot *f) = 0;

	virtual void visitModelFieldType(IModelFieldType *f) = 0;

	virtual void visitModelFieldVec(IModelFieldVec *f) = 0;

	virtual void visitModelFieldVecRoot(IModelFieldVecRoot *f) = 0;

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) = 0;

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) = 0;

	virtual void visitTypeConstraintIfElse(ITypeConstraintIfElse *c) = 0;

	virtual void visitTypeConstraintImplies(ITypeConstraintImplies *c) = 0;

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) = 0;

	virtual void visitTypeConstraintSoft(ITypeConstraintSoft *c) = 0;

	virtual void visitTypeConstraintUnique(ITypeConstraintUnique *c) = 0;

	virtual void visitTypeExprBin(ITypeExprBin *e) = 0;

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) = 0;

	virtual void visitTypeExprRange(ITypeExprRange *e) = 0;

	virtual void visitTypeExprRangelist(ITypeExprRangelist *e) = 0;

	virtual void visitTypeExprVal(ITypeExprVal *e) = 0;

	virtual void visitTypeField(ITypeField *f) = 0;

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) = 0;

	virtual void visitTypeFieldRef(ITypeFieldRef *f) = 0;

	virtual void visitTypeFieldVec(ITypeFieldVec *f) = 0;


};

}



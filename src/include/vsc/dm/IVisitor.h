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
namespace dm {

class IDataTypeArray;
class IDataTypeBool;
class IDataTypeEnum;
class IDataTypeInt;
class IDataTypeList;
class IDataTypePtr;
class IDataTypeString;
class IDataTypeStruct;
class IDataTypeTypeRef;
class IDataTypeWrapper;

class IModelConstraint;
class IModelConstraintBlock;
class IModelConstraintExpr;
class IModelConstraintForeach;
class IModelConstraintIfElse;
class IModelConstraintImplies;
class IModelConstraintRef;
class IModelConstraintScope;
class IModelConstraintSelect;
class IModelConstraintSoft;
class IModelConstraintSubst;
class IModelConstraintUnique;

class IModelCoverBinCollection;
class IModelCoverBinMask;
class IModelCoverBinSingleRange;
class IModelCoverBinSingleVal;
class IModelCoverCross;
class IModelCovergroup;
class IModelCoverpoint;

class IModelExprBin;
class IModelExprCond;
class IModelExprFieldRef;
class IModelExprIn;
class IModelExprIndexedFieldRef;
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
class IModelFieldTypeRef;
class IModelFieldVec;
class IModelFieldVecRoot;

class ITypeConstraint;
class ITypeConstraintBlock;
class ITypeConstraintExpr;
class ITypeConstraintForeach;
class ITypeConstraintIfElse;
class ITypeConstraintImplies;
class ITypeConstraintScope;
class ITypeConstraintSoft;
class ITypeConstraintUnique;
class ITypeExpr;
class ITypeExprArrIndex;
class ITypeExprArrayLiteral;
class ITypeExprBin;
class ITypeExprEnumRef;
class ITypeExprFieldRef;
class ITypeExprRange;
class ITypeExprRangelist;
class ITypeExprRef;
class ITypeExprRefBottomUp;
class ITypeExprRefInline;
class ITypeExprRefPath;
class ITypeExprRefTopDown;
class ITypeExprStructLiteral;
class ITypeExprSubField;
class ITypeExprUnary;
class ITypeExprVal;
class ITypeField;
class ITypeFieldPhy;
class ITypeFieldRef;
class ITypeFieldVec;

class IVisitor {
public:

	virtual ~IVisitor() { }

	virtual bool cascade() const = 0;

	virtual void visitDataTypeArray(IDataTypeArray *t) = 0;

	virtual void visitDataTypeBool(IDataTypeBool *t) = 0;

	virtual void visitDataTypeEnum(IDataTypeEnum *t) = 0;

	virtual void visitDataTypeInt(IDataTypeInt *t) = 0;

	virtual void visitDataTypeList(IDataTypeList *t) = 0;

	virtual void visitDataTypePtr(IDataTypePtr *t) = 0;

	virtual void visitDataTypeString(IDataTypeString *t) = 0;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) = 0;

	virtual void visitDataTypeTypeRef(IDataTypeTypeRef *t) = 0;

	virtual void visitDataTypeWrapper(IDataTypeWrapper *t) = 0;

	virtual void visitModelConstraint(IModelConstraint *c) = 0;

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) = 0;

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) = 0;

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) = 0;

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) = 0;

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) = 0;

	virtual void visitModelConstraintRef(IModelConstraintRef *c) = 0;

	virtual void visitModelConstraintScope(IModelConstraintScope *c) = 0;

	virtual void visitModelConstraintSelect(IModelConstraintSelect *c) = 0;

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) = 0;

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) = 0;

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) = 0;

	virtual void visitModelCoverBinCollection(IModelCoverBinCollection *c) = 0;

	virtual void visitModelCoverBinMask(IModelCoverBinMask *c) = 0;

	virtual void visitModelCoverBinSingleRange(IModelCoverBinSingleRange *c) = 0;

	virtual void visitModelCoverBinSingleVal(IModelCoverBinSingleVal *c) = 0;

	virtual void visitModelCoverCross(IModelCoverCross *c) = 0;

	virtual void visitModelCovergroup(IModelCovergroup *c) = 0;

	virtual void visitModelCoverpoint(IModelCoverpoint *c) = 0;

	virtual void visitModelExprBin(IModelExprBin *e) = 0;

	virtual void visitModelExprCond(IModelExprCond *e) = 0;

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) = 0;

	virtual void visitModelExprIn(IModelExprIn *e) = 0;

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) = 0;

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

	virtual void visitModelFieldRefType(IModelFieldTypeRef *f) = 0;

	virtual void visitModelFieldRoot(IModelFieldRoot *f) = 0;

	virtual void visitModelFieldType(IModelFieldType *f) = 0;

	virtual void visitModelFieldVec(IModelFieldVec *f) = 0;

	virtual void visitModelFieldVecRoot(IModelFieldVecRoot *f) = 0;

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) = 0;

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) = 0;

	virtual void visitTypeConstraintForeach(ITypeConstraintForeach *c) = 0;

	virtual void visitTypeConstraintIfElse(ITypeConstraintIfElse *c) = 0;

	virtual void visitTypeConstraintImplies(ITypeConstraintImplies *c) = 0;

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) = 0;

	virtual void visitTypeConstraintSoft(ITypeConstraintSoft *c) = 0;

	virtual void visitTypeConstraintUnique(ITypeConstraintUnique *c) = 0;

	virtual void visitTypeExprArrayLiteral(ITypeExprArrayLiteral *e) = 0;

	virtual void visitTypeExprArrIndex(ITypeExprArrIndex *e) = 0;

	virtual void visitTypeExprBin(ITypeExprBin *e) = 0;

    virtual void visitTypeExprEnumRef(ITypeExprEnumRef *e) = 0;

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) = 0;

	virtual void visitTypeExprRange(ITypeExprRange *e) = 0;

	virtual void visitTypeExprRangelist(ITypeExprRangelist *e) = 0;

	virtual void visitTypeExprRef(ITypeExprRef *e) = 0;

	virtual void visitTypeExprRefBottomUp(ITypeExprRefBottomUp *e) = 0;

	virtual void visitTypeExprRefInline(ITypeExprRefInline *e) = 0;

	virtual void visitTypeExprRefPath(ITypeExprRefPath *e) = 0;

	virtual void visitTypeExprRefTopDown(ITypeExprRefTopDown *e) = 0;

    virtual void visitTypeExprStructLiteral(ITypeExprStructLiteral *e) = 0;

	virtual void visitTypeExprSubField(ITypeExprSubField *e) = 0;

	virtual void visitTypeExprUnary(ITypeExprUnary *e) = 0;

	virtual void visitTypeExprVal(ITypeExprVal *e) = 0;

	virtual void visitTypeField(ITypeField *f) = 0;

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) = 0;

	virtual void visitTypeFieldRef(ITypeFieldRef *f) = 0;

	virtual void visitTypeFieldVec(ITypeFieldVec *f) = 0;


};

}
}



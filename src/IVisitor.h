
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

class DataTypeInt;
class DataTypeStruct;

class ModelConstraint;
class ModelConstraintExpr;
class ModelConstraintScope;
class ModelConstraintSoft;

class ModelExprBin;
class ModelExprFieldRef;

class ModelField;
class ModelFieldRoot;
class ModelFieldType;

class TypeField;

class IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitDataTypeInt(DataTypeInt *t) = 0;

	virtual void visitDataTypeStruct(DataTypeStruct *t) = 0;

	virtual void visitModelConstraint(ModelConstraint *c) = 0;

	virtual void visitModelConstraintExpr(ModelConstraintExpr *c) = 0;

	virtual void visitModelConstraintScope(ModelConstraintScope *c) = 0;

	virtual void visitModelConstraintSoft(ModelConstraintSoft *c) = 0;

	virtual void visitModelExprBin(ModelExprBin *e) = 0;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) = 0;

	virtual void visitModelField(ModelField *f) = 0;

	virtual void visitModelFieldRoot(ModelFieldRoot *f) = 0;

	virtual void visitModelFieldType(ModelFieldType *f) = 0;

	virtual void visitTypeField(TypeField *f) = 0;

};

}



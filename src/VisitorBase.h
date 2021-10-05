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
#include "DataTypeInt.h"
#include "DataTypeStruct.h"


#include "IVisitor.h"

#include "ModelExprBin.h"
#include "ModelExprFieldRef.h"

#include "ModelFieldRoot.h"
#include "ModelFieldType.h"
#include "TypeField.h"

namespace vsc {

class VisitorBase : public virtual IVisitor {
public:

	VisitorBase();

	virtual ~VisitorBase();

	virtual void visitDataTypeInt(DataTypeInt *t) override;

	virtual void visitDataTypeStruct(DataTypeStruct *t) override;

	virtual void visitModelExprBin(ModelExprBin *e) override;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) override;

	virtual void visitModelField(ModelField *f) override;

	virtual void visitModelFieldRoot(ModelFieldRoot *f) override;

	virtual void visitModelFieldType(ModelFieldType *f) override;

	virtual void visitTypeField(TypeField *f) override;

};

} /* namespace vsc */


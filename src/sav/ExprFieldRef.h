
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
 * ExprFieldRef.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#pragma once
#include "sav/Expr.h"
#include "sav/Field.h"

namespace vsc {

class ExprFieldRef : public Expr {
public:
	ExprFieldRef(FieldSP field);

	ExprFieldRef(Field *field);

	virtual ~ExprFieldRef();

	Field *field() const { return m_field; }

	virtual void accept(IVisitor *v) { v->visitExprFieldRef(this); }

	static ExprSP mk(FieldSP field);

private:
	FieldSP				m_field_sp;
	Field				*m_field;
};

} /* namespace vsc */


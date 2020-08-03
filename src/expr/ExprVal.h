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
 * ExprVal.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include <memory>
#include "IAccept.h"

namespace vsc {

enum ExprValType {
	ValType_Enum,
	ValType_Numeric,
};

class ExprVal;
typedef std::shared_ptr<ExprVal> ExprValSP;

class ExprVal : public IAccept {
public:
	ExprVal(ExprValType type);

	virtual ~ExprVal();

	ExprValType type() const { return m_type; }

	virtual bool eq(ExprValSP o) = 0;

	virtual bool eq(ExprVal *o) = 0;

	virtual bool ne(ExprValSP o) = 0;

	virtual bool ne(ExprVal *o) = 0;

	virtual std::string toString() const = 0;

private:
	ExprValType			m_type;

};


} /* namespace vsc */


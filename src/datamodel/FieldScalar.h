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
 * FieldScalar.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#pragma once
#include "datamodel/Field.h"
#include "expr/ExprValNumeric.h"

namespace vsc {

class FieldScalar;
typedef std::shared_ptr<FieldScalar> FieldScalarSP;

class FieldScalar : public Field {
public:
	FieldScalar(
			const std::string		&name,
			int32_t					width,
			bool					is_signed,
			bool					is_rand);

	virtual ~FieldScalar();

	virtual int32_t width() const { return m_val->width(); }

	virtual bool is_signed() const { return m_val->is_signed(); }

	virtual ExprValSP val() const {
		return m_val;
	}

	// Provide convenience method for obtaining a numeric value
	virtual ExprValNumericSP val_num() const {
		return m_val;
	}

	virtual void val(ExprValNumericSP v) { m_val = v; }


	virtual void accept(IVisitor *v) { v->visitFieldScalar(this); }

	static FieldScalarSP mk(
			const std::string 	&name,
			int32_t				width,
			bool				is_signed,
			bool				is_rand);

private:
	ExprValNumericSP				m_val;

};

} /* namespace vsc */


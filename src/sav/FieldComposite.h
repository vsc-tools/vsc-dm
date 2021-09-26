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
 * FieldComposite.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#pragma once
#include <vector>

#include "ConstraintBlock.h"
#include "sav/Field.h"

namespace vsc {

class FieldComposite : public Field {
public:
	FieldComposite(
			const std::string			&name,
			bool						is_rand);

	virtual ~FieldComposite();

	const std::vector<FieldSP> &children() const { return m_children; }

	FieldSP add_field(FieldSP f) {
		m_children.push_back(f);
		return f;
	}

	FieldSP addField(FieldSP f) {
		m_children.push_back(f);
		return f;
	}

	FieldSP addField(Field *f) {
		FieldSP ret(f);
		m_children.push_back(ret);
		return ret;
	}

	void addConstraint(ConstraintBlockSP c) { m_constraints.push_back(c); }

	ConstraintBlockSP addConstraint(
			const std::string						&name,
			std::initializer_list<ConstraintStmt *> c);

	const std::vector<ConstraintBlockSP> &constraints() const { return m_constraints; }

	virtual void set_used_rand(bool used_rand, int32_t level=0);

	// TODO: throw exception?
	virtual ExprValSP val() const { return ExprValSP(0); }

	virtual void accept(IVisitor *v) { v->visitFieldComposite(this); }

private:
	std::vector<FieldSP>				m_children;
	std::vector<ConstraintBlockSP>		m_constraints;
	// TODO: constraint_model
	// ...

};

typedef std::shared_ptr<FieldComposite> FieldCompositeSP;

} /* namespace vsc */


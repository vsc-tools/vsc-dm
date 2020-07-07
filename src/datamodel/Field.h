
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
 * Field.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_FIELD_H_
#define SRC_DATAMODEL_FIELD_H_
#include <string>
#include <memory>
#include "IVisitor.h"
#include "solver/ISolverData.h"

namespace vsc {

class Field {
public:

	Field(const std::string &name, bool is_rand);

	virtual ~Field();

	const std::string &name() const { return m_name; }

	std::string fullname() const;

	Field *parent() const { return m_parent; }

	void parent(Field *p) { m_parent = p; }

	int32_t idx() const { return m_idx; }

	void idx(int32_t i) { m_idx = i; }

	bool used_rand() const { return m_used_rand; }

	ISolverData *solver_data() const {
		return m_solver_data.get();
	}

	void solver_data(ISolverData *d) {
		m_solver_data = ISolverDataUP(d);
	}

	virtual void pre_randomize() { }

	virtual void post_randomize() { }

	virtual void set_used_rand(bool used_rand, int32_t level=0);

	virtual void accept(IVisitor *v) = 0;

protected:
	const std::string		m_name;
	Field					*m_parent;
	int32_t					m_idx;
	bool					m_decl_rand;
	bool					m_used_rand;
	ISolverDataUP			m_solver_data;

};

typedef std::shared_ptr<Field> FieldSP;

} /* namespace vsc */

#endif /* SRC_DATAMODEL_FIELD_H_ */

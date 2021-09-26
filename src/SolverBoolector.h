
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
 * SolverInstBoolector.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include <map>
#include <unordered_map>

#include "ISolver.h"

struct BoolectorNode;
struct Btor;

namespace vsc {

//struct BoolectorSort;

class SolverBoolector : public virtual ISolver {
public:
	SolverBoolector();

	virtual ~SolverBoolector();

	// Creates solver data for a field (and possibly sub-fields)
	virtual void initField(ModelField *f) override;

	// Creates solver data for a constraint
	virtual void initConstraint(ModelConstraint *c) override;

	virtual void addAssume(ModelConstraint *c) override;

	virtual void addAssert(ModelConstraint *c) override;

	virtual bool isSAT() override;

	virtual void finalizeField(ModelField *f) override;

private:

//	BoolectorSort get_sort(int32_t width);

private:
	Btor													*m_btor;

	std::unordered_map<ModelField *,BoolectorNode *>		m_field_node_m;
	std::unordered_map<ModelConstraint *,BoolectorNode *>	m_constraint_node_m;
	std::unordered_map<uint32_t, uint32_t>					m_sort_m;

};

} /* namespace vsc */


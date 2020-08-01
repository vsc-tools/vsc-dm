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
 * ConstraintBlock.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#pragma once
#include <memory>
#include <initializer_list>
#include "ConstraintScope.h"

namespace vsc {

class ConstraintBlock;
typedef std::shared_ptr<ConstraintBlock> ConstraintBlockSP;

class ConstraintBlock : public ConstraintScope {
public:
	ConstraintBlock(const std::string				&name);

	ConstraintBlock(
			const std::string						&name,
			std::initializer_list<ConstraintStmt *>	constraints);

	ConstraintBlock(
			std::initializer_list<ConstraintStmt *>	constraints);

	virtual ~ConstraintBlock();

	const std::string &name() const { return m_name; }

	void enabled(bool e) { m_enabled = e; }

	bool enabled() const { return m_enabled; }

	static ConstraintBlockSP toBlock(ConstraintStmtSP c);

	virtual void accept(IVisitor *v) { v->visitConstraintBlock(this); }

	static ConstraintBlockSP mk(std::initializer_list<ConstraintStmt *>	c);

	static ConstraintBlockSP mk(
			const std::string						&name,
			std::initializer_list<ConstraintStmt *>	c);

private:
	std::string					m_name;
	bool						m_enabled;

};


} /* namespace vsc */


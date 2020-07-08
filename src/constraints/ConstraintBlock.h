
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

#ifndef SRC_CONSTRAINTS_CONSTRAINTBLOCK_H_
#define SRC_CONSTRAINTS_CONSTRAINTBLOCK_H_
#include <memory>
#include <initializer_list>
#include "ConstraintScope.h"

namespace vsc {

class ConstraintBlock : public ConstraintScope {
public:
	ConstraintBlock(
			const std::string						&name,
			std::initializer_list<ConstraintStmt *>	constraints);

	virtual ~ConstraintBlock();

	virtual void accept(IVisitor *v) { v->visitConstraintBlock(this); }

};

typedef std::shared_ptr<ConstraintBlock> ConstraintBlockSP;

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTBLOCK_H_ */

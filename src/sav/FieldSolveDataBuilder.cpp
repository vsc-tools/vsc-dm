
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
 * FieldSolveDataBuilder.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "sav/FieldSolveDataBuilder.h"

namespace vsc {

FieldSolveDataBuilder::FieldSolveDataBuilder(ISolverInst *inst) : m_inst(inst) {
	// TODO Auto-generated constructor stub

}

FieldSolveDataBuilder::~FieldSolveDataBuilder() {
	// TODO Auto-generated destructor stub
}

void FieldSolveDataBuilder::visitFieldScalar(FieldScalar *f) {
//	f->solver_data(m_inst->createFieldInst(f));
}

} /* namespace vsc */

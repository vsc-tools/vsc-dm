
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
 * FieldSolveDataBuilder.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "../ISolver.h"
#include "../VisitorBase.h"

namespace vsc {

/**
 * Builds solve data for each field, and adds any
 * domain constraints -- eg for enum-type fields
 */
class FieldSolveDataBuilder : public VisitorBase {
public:
	FieldSolveDataBuilder(ISolver *inst);

	virtual ~FieldSolveDataBuilder();

	virtual void visitFieldScalar(FieldScalar *f) override;

private:
	ISolver				*m_inst;


};

} /* namespace vsc */


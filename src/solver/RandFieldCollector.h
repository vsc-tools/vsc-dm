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
 * RandFieldCollector.h
 *
 *  Created on: Jul 10, 2020
 *      Author: ballance
 */

#pragma once
#include <vector>
#include "VisitorBase.h"
#include "FieldScalar.h"


namespace vsc {

class RandFieldCollector : public VisitorBase {
public:
	RandFieldCollector();

	virtual ~RandFieldCollector();

	void collect(
			const std::vector<FieldSP> 		&fields,
			std::vector<FieldScalar *>		&rand_fields);

	virtual void visitFieldScalar(FieldScalar *f) override;


private:
	std::vector<FieldScalar *>			*m_rand_fields;

};

} /* namespace vsc */


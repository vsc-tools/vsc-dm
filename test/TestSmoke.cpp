
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
 * TestSmoke.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "TestSmoke.h"

#include "vsc.h"
#include "TestUtil.h"

namespace vsc {

TestSmoke::TestSmoke() {
	// TODO Auto-generated constructor stub

}

TestSmoke::~TestSmoke() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestSmoke, smoke) {
	fprintf(stdout, "Hello\n");
	vsc::FieldScalarSP a(new vsc::FieldScalar("a", 32, false, true));

	vsc::IRandomizer *randomizer = RandomizerFactory::inst();

	vsc::ConstraintBlockSP c(new vsc::ConstraintBlock(
			"c",
			{
				TestUtil::Constraint(TestUtil::Gt(a, 0)),
				TestUtil::Constraint(TestUtil::Lt(a, 10))
			}
			));
	std::vector<FieldSP> fields = {a};
	std::vector<ConstraintBlockSP> constraints = {c};

	for (uint32_t i=0; i<10; i++) {
		randomizer->randomize(0, fields, constraints);
		ASSERT_GT(a->val_num()->val_u(), 0);
		ASSERT_LT(a->val_num()->val_u(), 10);
	}
}

TEST_F(TestSmoke, smoke2) {

}

} /* namespace vsc */

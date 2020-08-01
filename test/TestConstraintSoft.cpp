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
 * TestConstraintSoft.cpp
 *
 *  Created on: Jul 12, 2020
 *      Author: ballance
 */

#include "TestConstraintSoft.h"
#include "TestUtil.h"

namespace vsc {

TestConstraintSoft::TestConstraintSoft() {
	// TODO Auto-generated constructor stub

}

TestConstraintSoft::~TestConstraintSoft() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestConstraintSoft, smoke) {
	vsc::FieldScalarSP a(new vsc::FieldScalar("a", 32, false, true));

	vsc::IRandomizer *randomizer = RandomizerFactory::inst();

	vsc::ConstraintStmtSP c(new vsc::ConstraintBlock(
			"c",
			{
				TestUtil::Constraint(TestUtil::Gt(a, 0)),
				TestUtil::Constraint(TestUtil::Lt(a, 10)),
				TestUtil::Soft(TestUtil::Lt(a, 1)),
				TestUtil::Soft(TestUtil::Gt(a, 1)),
				TestUtil::Soft(TestUtil::Lt(a, 4)),
				TestUtil::Soft(TestUtil::Gt(a, 5))
			}
			));
	std::vector<FieldSP> fields = {a};
	std::vector<ConstraintStmtSP> constraints = {c};
	uint32_t *hist = (uint32_t *)alloca(sizeof(uint32_t)*9);
	memset(hist, 0, sizeof(uint32_t)*9);

	for (uint32_t i=0; i<40; i++) {
		randomizer->randomize(fields, constraints);
		fprintf(stdout, "a=%lld\n", a->val_num()->val_s());
		hist[a->val_num()->val_u()-1]++;
		ASSERT_GT(a->val_num()->val_u(), 5);
		ASSERT_LT(a->val_num()->val_u(), 10);
	}

	fprintf(stdout, "hist: ");
	for (uint32_t i=0; i<9; i++) {
		fprintf(stdout, "%d ", hist[i]);
	}
	fprintf(stdout, "\n");
}


} /* namespace vsc */

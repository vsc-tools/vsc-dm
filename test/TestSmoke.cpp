
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

	vsc::ConstraintStmtSP c(new vsc::ConstraintBlock(
			"c",
			{
				TestUtil::Constraint(TestUtil::Gt(a, 0)),
				TestUtil::Constraint(TestUtil::Lt(a, 10))
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
		ASSERT_GT(a->val_num()->val_u(), 0);
		ASSERT_LT(a->val_num()->val_u(), 10);
	}

	fprintf(stdout, "hist: ");
	for (uint32_t i=0; i<9; i++) {
		fprintf(stdout, "%d ", hist[i]);
	}
	fprintf(stdout, "\n");
}

TEST_F(TestSmoke, smoke_2var) {
	fprintf(stdout, "Hello\n");
	vsc::FieldScalarSP a(new vsc::FieldScalar("a", 32, false, true));
	vsc::FieldScalarSP b(new vsc::FieldScalar("b", 32, false, true));

	vsc::IRandomizer *randomizer = RandomizerFactory::inst();

	vsc::ConstraintStmtSP c(new vsc::ConstraintBlock(
			"c",
			{
				TestUtil::Constraint(TestUtil::Gt(a, 0)),
				TestUtil::Constraint(TestUtil::Lt(a, 10)),
				TestUtil::Constraint(TestUtil::Gt(b, 0)),
				TestUtil::Constraint(TestUtil::Lt(b, 10)),
				TestUtil::Constraint(TestUtil::Lt(a, b))
			}
			));
	std::vector<FieldSP> fields = {a, b};
	std::vector<ConstraintStmtSP> constraints = {c};
	uint32_t *hist_a = (uint32_t *)alloca(sizeof(uint32_t)*9);
	memset(hist_a, 0, sizeof(uint32_t)*9);
	uint32_t *hist_b = (uint32_t *)alloca(sizeof(uint32_t)*9);
	memset(hist_b, 0, sizeof(uint32_t)*9);

	for (uint32_t i=0; i<40; i++) {
		randomizer->randomize(fields, constraints);
		fprintf(stdout, "a=%lld\n", a->val_num()->val_s());
		hist_a[a->val_num()->val_u()-1]++;
		hist_b[b->val_num()->val_u()-1]++;
		ASSERT_GT(a->val_num()->val_u(), 0);
		ASSERT_LT(a->val_num()->val_u(), 10);
		ASSERT_GT(b->val_num()->val_u(), 0);
		ASSERT_LT(b->val_num()->val_u(), 10);
		ASSERT_LT(a->val_num()->val_u(), b->val_num()->val_u());
	}

	fprintf(stdout, "hist_a: ");
	for (uint32_t i=0; i<9; i++) {
		fprintf(stdout, "%d ", hist_a[i]);
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "hist_b: ");
	for (uint32_t i=0; i<9; i++) {
		fprintf(stdout, "%d ", hist_b[i]);
	}
	fprintf(stdout, "\n");

	for (uint32_t i=0; i<8; i++) { // Only values 0..8 will be present
		ASSERT_NE(hist_a[i], 0);
	}
	for (uint32_t i=1; i<9; i++) { // Only values 1..9 will be present
		ASSERT_NE(hist_b[i], 0);
	}
}


TEST_F(TestSmoke, smoke_wider) {
	fprintf(stdout, "Hello\n");
	vsc::FieldScalarSP a(new vsc::FieldScalar("a", 32, false, true));

	vsc::IRandomizer *randomizer = RandomizerFactory::inst();

	vsc::ConstraintStmtSP c(new vsc::ConstraintBlock(
			"c",
			{
				TestUtil::Constraint(TestUtil::Gt(a, 0)),
				TestUtil::Constraint(TestUtil::Lt(a, 128))
			}
			));
	std::vector<FieldSP> fields = {a};
	std::vector<ConstraintStmtSP> constraints = {c};
	uint32_t *hist = (uint32_t *)alloca(sizeof(uint32_t)*127);
	memset(hist, 0, sizeof(uint32_t)*127);

	for (uint32_t i=0; i<(128*20); i++) {
		randomizer->randomize(fields, constraints);
		hist[a->val_num()->val_u()-1]++;
		ASSERT_GT(a->val_num()->val_u(), 0);
		ASSERT_LT(a->val_num()->val_u(), 128);
	}

	fprintf(stdout, "hist: ");
	for (uint32_t i=0; i<127; i++) {
		fprintf(stdout, "%d ", hist[i]);
	}
	fprintf(stdout, "\n");

	// Confirm that we filled in the range
	for (uint32_t i=0; i<127; i++) {
		ASSERT_NE(hist[i], 0);
	}
}

TEST_F(TestSmoke, perf) {
	vsc::FieldScalarSP a(new vsc::FieldScalar("a", 32, false, true));

	vsc::IRandomizer *randomizer = RandomizerFactory::inst();

	vsc::ConstraintStmtSP c(new vsc::ConstraintBlock(
			"c",
			{
				TestUtil::Constraint(TestUtil::Gt(a, 0)),
				TestUtil::Constraint(TestUtil::Lt(a, 10))
			}
			));
	std::vector<FieldSP> fields = {a};
	std::vector<ConstraintStmtSP> constraints = {c};

	uint32_t count = 1000;
	uint64_t start = TestUtil::time_ms();
	for (uint32_t i=0; i<count; i++) {
		randomizer->randomize(fields, constraints);
		ASSERT_GT(a->val_num()->val_u(), 0);
		ASSERT_LT(a->val_num()->val_u(), 10);
	}
	uint64_t end = TestUtil::time_ms();

	fprintf(stdout, "%d iterations in %d ms\n", count, uint32_t(end-start));
}

TEST_F(TestSmoke, perf2) {

	vsc::IRandomizer *randomizer = RandomizerFactory::inst();

	std::vector<FieldSP> fields;
	std::vector<ConstraintStmtSP> constraints;

	for (uint32_t i=0; i<100; i++) {
		vsc::FieldScalarSP a(new vsc::FieldScalar("a", 32, false, true));
		vsc::ConstraintStmtSP c(new vsc::ConstraintBlock(
				"c",
				{
						TestUtil::Constraint(TestUtil::Gt(a, 0)),
						TestUtil::Constraint(TestUtil::Lt(a, 10))
				}
				));
		fields.push_back(a);
		constraints.push_back(c);
	}

	uint32_t count = 1000;
	uint64_t start = TestUtil::time_ms();
	for (uint32_t i=0; i<count; i++) {
		randomizer->randomize(fields, constraints);
//		ASSERT_GT(a->val_num()->val_u(), 0);
//		ASSERT_LT(a->val_num()->val_u(), 10);
	}
	uint64_t end = TestUtil::time_ms();

	fprintf(stdout, "%d iterations in %d ms\n", count, uint32_t(end-start));
}


TEST_F(TestSmoke, smoke2) {

}

} /* namespace vsc */

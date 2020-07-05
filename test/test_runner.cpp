
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
 * test_runner.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */
#include <string>
#include <stdio.h>
#include "gtest/gtest.h"

class JUnitResultListener : public ::testing::EmptyTestEventListener {
public:
	JUnitResultListener(
			const std::string &result) {
		m_out = fopen(result.c_str(), "w");
	}

	virtual void OnTestProgramStart(const testing::UnitTest &unit_test) {
		fprintf(stdout, "OnTestProgramStart\n");
	}

	virtual void OnTestProgramEnd(const testing::UnitTest &unit_test) {
//		fprintf(m_out, "<testsuites tests=\"%d\" failures=\"%d\" time=\"%f\" name=\"Syntax Parsing Tests\">\n",
//				unit_test.total_test_case_count(),
//				unit_test.failed_test_case_count(),
//				unit_test.elapsed_time());
		fprintf(m_out, "<testsuites>\n");
		fprintf(m_out, "%s", m_details.c_str());
		fprintf(m_out, "</testsuites>\n");
		fclose(m_out);
	}

	virtual void OnTestCaseStart(const testing::TestCase &test_case) {
		m_test = "";
		m_testcase = test_case.name();
	}

	virtual void OnTestCaseEnd(const testing::TestCase &test_case) {
		char tmp[1024];
		m_details += "    <testsuite id=\"";
		m_details += test_case.name();
		m_details += "\" ";

		double elapsed_time = test_case.elapsed_time();
		elapsed_time /= 1000;

		sprintf(tmp, "tests=\"%d\" failures=\"%d\" time=\"%f\" name=\"%s\">\n",
				test_case.total_test_count(),
				test_case.failed_test_count(),
				test_case.name(),
				elapsed_time);
		m_details += tmp;
		m_details += m_test;
		m_details += "    </testsuite>\n";
	}

	virtual void OnTestStart(const testing::TestInfo &test_info) {
		m_test += "        <testcase id=\"";
		m_test += m_testcase + "." + test_info.name() + "\"";
		m_test += " name=\"";
		m_test += test_info.name();
		m_test += "\">\n";
	}

	virtual void OnTestPartResult(const testing::TestPartResult &result) {
		m_test += "            <failure message=\"";
		m_test += result.summary();
		m_test += "\" type=\"ERROR\">\n";
		m_test += result.message();
		m_test += "            </failure>\n";
		m_test += "        </testcase>\n";
	}

	virtual void OnTestEnd(const testing::TestInfo &test_info) {
		m_test += "        </testcase>\n";
	}


private:
	std::string			m_test;
	std::string			m_details;
	std::string			m_testcase;
	FILE				*m_out;

};

int main(int argc, char **argv) {
	std::string result = "results.xml";

	::testing::InitGoogleTest(&argc, argv);

	JUnitResultListener *listener = new JUnitResultListener(result);
	::testing::UnitTest::GetInstance()->listeners().Append(listener);

	int ret = RUN_ALL_TESTS();


	return ret;
}



/*
 * TestSmoke.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef TEST_TESTSMOKE_H_
#define TEST_TESTSMOKE_H_
#include "gtest/gtest.h"

namespace vsc {

class TestSmoke : public testing::Test {
public:
	TestSmoke();
	virtual ~TestSmoke();
};

} /* namespace vsc */

#endif /* TEST_TESTSMOKE_H_ */

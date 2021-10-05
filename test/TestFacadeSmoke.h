/*
 * TestFacadeSmoke.h
 *
 *  Created on: Oct 3, 2021
 *      Author: mballance
 */

#pragma once
#include "gtest/gtest.h"
#include "vsc_facade.h"

namespace vsc {

class TestFacadeSmoke : public ::testing::Test {
public:
	TestFacadeSmoke();

	virtual ~TestFacadeSmoke();
};

} /* namespace vsc */


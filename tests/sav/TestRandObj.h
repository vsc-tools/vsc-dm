/*
 * TestRandObj.h
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#pragma once
#include "gtest/gtest.h"
#include "vsc_facade.h"


namespace vsc {

using namespace facade;

class TestRandObj : public testing::Test {
public:
	TestRandObj();

	virtual ~TestRandObj();

};

}

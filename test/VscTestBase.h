/*
 * VscTestBase.h
 *
 *  Created on: Oct 6, 2021
 *      Author: mballance
 */

#pragma once
#include "gtest/gtest.h"

namespace vsc {

class VscTestBase : public ::testing::Test {
public:
	VscTestBase();

	virtual ~VscTestBase();

	virtual void SetUp() override;

	virtual void TearDown() override;


};

} /* namespace vsc */


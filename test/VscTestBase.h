/*
 * VscTestBase.h
 *
 *  Created on: Oct 6, 2021
 *      Author: mballance
 */

#pragma once
#include "glog/logging.h"
#include "gtest/gtest.h"


namespace vsc {

class VscTestBase : public ::testing::Test, public virtual ::google::LogSink {
public:
	VscTestBase();

	virtual ~VscTestBase();

	virtual void SetUp() override;

	virtual void TearDown() override;

	virtual void send(::google::LogSeverity severity, const char* full_filename,
	                    const char* base_filename, int line,
	                    const struct ::tm* tm_time,
	                    const char* message, size_t message_len) override;

};

} /* namespace vsc */

